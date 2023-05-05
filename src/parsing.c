#include "minishell.h"

/* WARNING: Quoted vs unquoted here-doc limiter */
/* WARNING: `cat |<env.c grep void -> cat: write error: Broken pipe */

/* TODO: Add support for ~ expansion */
/* TODO: Run all examples from the example sheet */
/* TODO: Deal with all remaining FIXME */
/*
 * - Turn the readline buffer into a doubly-linked list with one char per
 *   node.
 * - Mark the quote state for each node.
 * - Give the same index for each node which belongs to the same word.
 * - Give the same index for each node which belongs to the same command.
 * - Delete all unquoted spaces.
 * - Look for syntax errors e.g line with a single | or a single pair of
 *   quotes.
 * - Delete unquoted quotes and unquoted pipes.
 *      - WARNING: MS $ '' should produce a node with word member set to
 *        the empty string.
 * - Concatenate nodes with the same word_index into one node (make words
 *   out of individual chars).
 * - Expand variables if necessary.
 * - Turn consecutive nodes with the same quote state into one node.
 * - Fill in type information
 * - Error checking (i.e file exists, program exists, file and folder
 *   permission etc.).
 */

/* PARSING */
void ps_token_list_from_array(t_token **tok, char *s)
{
	char buf[2];

	if (!tok || !s)
		return;
	buf[1] = '\0';
	while (*s)
	{
		buf[0] = *s++;
		ps_token_list_node_add(tok, ps_token_list_node_create(buf));
	}
}

void ps_token_list_print(t_token **tok)
{
	t_token *curr;

	curr = *tok;
	printf("%-15s | %-15s | %-15s | %-15s | %-15s\n", "type", "quote", "char *", "word", "cmd");
	printf("-------------------------------------------------------------------"
	       "--------\n");
	while (curr)
	{
		if (curr->word)
			printf("%-15d | %-15d | %-15s | %-15ld | %-15ld\n", curr->type, curr->quote, curr->word, curr->word_index, curr->cmd_index);
		curr = curr->next;
	}
	f_printf("\n");
}

/* PARSING */
bool ismeta(int c)
{
	return (c == '<' || c == '>' || c == '|' || c == ' ' || c == '\t' || c == '\n');
}

/* FIXME: Replace isprint with f_isprint */
int is_legal_var_char(int c)
{
	return (!ismeta(c) && isprint(c));
}

int ps_token_list_update_quote_state(char c, int state)
{
	if (c == '\'' && state == SIMPLE)
		state = NONE;
	else if (c == '"' && state == DOUBLE)
		state = NONE;
	else if (c == '\'' && state == NONE)
		state = SIMPLE;
	else if (c == '"' && state == NONE)
		state = DOUBLE;
	return (state);
}

void ps_token_list_mark_quotes(t_token **tok)
{
	t_token *curr;
	char     c;
	int      state;

	curr = *tok;
	state = NONE;
	while (curr)
	{
		c = curr->word[0];
		if (state == NONE && (c == '\'' || c == '"'))
		{
			curr->quote = NONE;
			state = ps_token_list_update_quote_state(c, state);
			curr = curr->next;
		}
		else
		{
			state = ps_token_list_update_quote_state(c, state);
			curr->quote = state;
			curr = curr->next;
		}
	}
}

/* FIXME: Check for edge cases with current approach */
void ps_token_list_set_index_cmd(t_token **tok)
{
	size_t   cmd;
	t_token *curr;
	t_token *next;
	char     arr[3];

	if (!tok)
		return;
	cmd = 0;
	curr = *tok;
	while (curr)
	{
		next = curr->next;
		if (next && next->word[0] == '|')
		{
			arr[0] = curr->word[0];
			arr[1] = next->word[0];
			if (next->next)
				arr[2] = next->next->word[0];
			else
				arr[2] = 0;
			if (f_isalnum(arr[0]) && f_isalnum(arr[2]))
				cmd++;
		}
		curr->cmd_index = cmd;
		curr = next;
	}
}

void ps_token_list_set_index_word(t_token **tok)
{
	size_t   word;
	t_token *curr;
	bool     sep;

	if (!tok)
		return;
	word = 0;
	sep = false;
	curr = *tok;
	while (curr)
	{
		if ((f_isspace(curr->word[0]) || curr->word[0] == '|') && !sep)
		{
			sep = true;
			word++;
		}
		else if (!(f_isspace(curr->word[0]) || curr->word[0] == '|') && sep)
		{
			sep = false;
			word++;
		}
		curr->word_index = word;
		curr = curr->next;
	}
}

int ps_token_list_has_syntax_error(t_token **tok)
{
	t_token *next;
	t_token *curr;

	if (!tok)
		return (0);
	curr = *tok;
	if (curr->word[0] == '|')
		return (f_perror(ERR_SYNTAX), 1);
	while (curr)
	{
		next = curr->next;
		if (ismeta(curr->word[0]) && curr->quote == NONE)
		{
			if (next && (curr->word[0] == '>' || curr->word[0] == '<') && (next->word[0] == '>' || next->word[0] == '<'))
				next = next->next;
			if ((next && ismeta(next->word[0])) || !next)
				return (f_perror(ERR_SYNTAX), 1);
		}
		curr = next;
	}
	return (0);
}

/* Update index to separate construct of the form >file into two words */
void ps_token_list_update_indices(t_token **tok)
{
	char     c;
	size_t   i;
	t_token *curr;

	if (!tok)
		return;
	i = 0;
	curr = *tok;
	while (curr)
	{
		if (curr->word[0] == '$')
			i++;
		curr->word_index += i;
		if ((curr->word[0] == '>' || curr->word[0] == '<') && curr->next)
		{
			c = curr->next->word[0];
			if (c != '<' && c != '>' && c != '|')
				i++;
		}
		curr = curr->next;
	}
}

void ps_token_list_delete_unquoted_spaces(t_token **tok)
{
	t_token *next;
	t_token *curr;

	if (!tok)
		return;
	curr = *tok;
	while (curr)
	{
		next = curr->next;
		if (curr->quote == NONE && f_isspace(curr->word[0]))
			ps_token_list_node_rm(tok, curr);
		curr = next;
	}
}

/* FIXME: Make the function shorter */
void ps_token_list_delete_unquoted_quotes(t_token **tok)
{
	t_token *next;
	t_token *curr;

	if (!tok)
		return;
	curr = *tok;
	while (curr)
	{
		next = curr->next;
		if (curr->quote == NONE && (curr->word[0] == '\'' || curr->word[0] == '"'))
		{
			if (next && (next->word[0] == curr->word[0]))
			{
				curr->word[0] = '\0';
				ps_token_list_node_rm(tok, next);
				curr = curr->next;
			}
			else
			{
				ps_token_list_node_rm(tok, curr);
				curr = next;
			}
		}
		else
			curr = curr->next;
	}
}

void ps_token_list_delete_unquoted_dollar(t_token **tok)
{
	t_token *next;
	t_token *curr;

	if (!tok)
		return;
	curr = *tok;
	while (curr)
	{
		next = curr->next;
		if (curr->quote == NONE && curr->word[0] == '$' && !curr->word[1])
			ps_token_list_node_rm(tok, curr);
		curr = next;
	}
}

void ps_token_list_delete_unquoted_brackets(t_token **tok)
{
	t_token *next;
	t_token *curr;

	if (!tok)
		return;
	curr = *tok;
	while (curr)
	{
		next = curr->next;
		if (curr->quote == NONE && curr->type == BASIC && (curr->word[0] == '<' || curr->word[0] == '>'))
			ps_token_list_node_rm(tok, curr);
		curr = next;
	}
}

void ps_token_list_delete_unquoted_pipes(t_token **tok)
{
	t_token *next;
	t_token *curr;

	if (!tok)
		return;
	curr = *tok;
	while (curr)
	{
		next = curr->next;
		if (next && curr->quote == NONE && curr->word[0] == '|' && !ismeta(next->word[0]))
			ps_token_list_node_rm(tok, curr);
		curr = next;
	}
}

void ps_token_list_recreate_words(t_token **tok)
{
	char    *tmp;
	t_token *curr;
	t_token *next;

	if (!tok || !*tok)
		return;
	curr = *tok;
	next = curr->next;
	while (curr)
	{
		next = curr->next;
		while (next && (curr->word_index == next->word_index) && (curr->quote == next->quote))
		{
			tmp = f_strjoin(curr->word, next->word);
			free(curr->word);
			curr->word = tmp;
			ps_token_list_node_rm(tok, next);
			next = curr->next;
		}
		curr = curr->next;
	}
}

void ps_token_list_recreate_variables(t_token **tok)
{
	char    *tmp;
	t_token *curr;
	t_token *next;

	if (!tok || !*tok)
		return;
	curr = *tok;
	next = curr->next;
	while (curr)
	{
		next = curr->next;
		while (next && curr->word[0] == '$' && is_legal_var_char(next->word[0]) && (curr->word_index == next->word_index) && (curr->quote == next->quote))
		{
			tmp = f_strjoin(curr->word, next->word);
			free(curr->word);
			curr->word = tmp;
			ps_token_list_node_rm(tok, next);
			next = curr->next;
		}
		curr = curr->next;
	}
}

bool ps_line_has_balanced_quotes(char *s)
{
	size_t nsimple;
	size_t ndouble;

	nsimple = 0;
	ndouble = 0;
	while (*s)
	{
		if (*s == '"')
			ndouble++;
		else if (*s == '\'')
			nsimple++;
		s++;
	}
	if (nsimple % 2 || ndouble % 2)
		return (false);
	return (true);
}

void ps_token_list_fill_type(t_token **tok)
{
	t_token *curr;

	if (!tok)
		return;
	curr = *tok;
	while (curr)
	{
		if (curr->quote == NONE)
		{
			if (!curr->next)
				break;
			if (!f_strcmp(curr->word, ">"))
				curr->next->type = S_OUTPUT;
			else if (!f_strcmp(curr->word, "<"))
				curr->next->type = S_INPUT;
			else if (!f_strcmp(curr->word, ">>"))
				curr->next->type = D_OUTPUT;
			else if (!f_strcmp(curr->word, "<<"))
				curr->next->type = D_INPUT;
		}
		curr = curr->next;
	}
}

/*
 * Unlike Bash, `echo [$HOME]` should not expand since `[` is actually a
 * built-in that we don't have to handle. Therefore `[` and `[[` are
 * treated as litteral characters. This goes for `echo \$HOME` which
 * produces `$HOME` in Bash but produces `\$HOME` here since `\` is not a
 * metacharacter in MSH.
 * https://unix.stackexchange.com/questions/99185/what-do-square-brackets-mean-without-the-if-on-the-left
 *
 * Also, variable names must be of the form [a-zA-Z_]+[a-zA-Z0-9_]*, so
 * `echo $USER- -> matthieu-`. Since we don't treat \ as a metacharacter
 * `echo $USER\ -> matthieu\`.
 * https://stackoverflow.com/questions/2821043/allowed-characters-in-linux-environment-variable-names
 */

/* FIXME: Handle $?USER -> 0USER, check if curr->word[0] == '$' &&
curr->word[1] == '?' if true call special function */
/* FIXME: echo $''HOME -> HOME */
void ps_token_list_expand_variables(t_token **tok, t_env **env)
{
	char    *value;
	t_token *curr;

	if (!tok)
		return;
	curr = *tok;
	while (curr)
	{
		/* FIXME: is_legal_var_name -> env_list_is_valid_id might break some stuff */
		if (curr->word[0] == '$' && curr->word[1] && env_list_is_valid_id(&curr->word[1]) && curr->quote != SIMPLE)
		{
			value = env_getenv(env, &curr->word[1]);
			free(curr->word);
			if (value)
				curr->word = value;
			else
			{
				curr->word = f_strdup("");
				free(value);
			}
		}
		curr = curr->next;
	}
}

/* Regroup words between quotes in one string */
void ps_token_list_group_words(t_token **tok)
{
	char    *tmp;
	t_token *curr;
	t_token *next;

	if (!tok || !*tok)
		return;
	curr = *tok;
	next = curr->next;
	while (curr)
	{
		next = curr->next;
		while (next && curr->quote != NONE && (curr->quote == next->quote))
		{
			tmp = f_strjoin(curr->word, next->word);
			free(curr->word);
			curr->word = tmp;
			ps_token_list_node_rm(tok, next);
			next = curr->next;
		}
		curr = curr->next;
	}
}

static int ps_token_list_parse(t_glb *glb)
{
	ps_token_list_mark_quotes(glb->tok);
	ps_token_list_set_index_word(glb->tok);
	ps_token_list_delete_unquoted_spaces(glb->tok);
	ps_token_list_delete_unquoted_quotes(glb->tok);
	ps_token_list_set_index_cmd(glb->tok);
	if (ps_token_list_has_syntax_error(glb->tok))
		return (1);
	ps_token_list_update_indices(glb->tok);
	ps_token_list_delete_unquoted_pipes(glb->tok);
	ps_token_list_recreate_variables(glb->tok);
	ps_token_list_expand_variables(glb->tok, glb->env);
	ps_token_list_recreate_words(glb->tok);
	ps_token_list_fill_type(glb->tok);
	ps_token_list_delete_unquoted_dollar(glb->tok);
	ps_token_list_delete_unquoted_brackets(glb->tok);
	ps_token_list_group_words(glb->tok);
	ps_token_list_print(glb->tok);
	return (0);
}

int parsing(t_glb *glb)
{
	if (ps_token_list_parse(glb))
		return (1);
	return (0);
}
