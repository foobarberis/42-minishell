#include "minishell.h"

/* gcc -Wall -Wextra -g3 -fsanitize=address -lreadline parsing.c ../mlc/libft.a -I../inc -I../mlc/inc */

/* WARNING: Quoted vs unquoted here-doc limiter */
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

/* LIST UTILS */
t_token	*ps_token_list_goto_last(t_token **tok)
{
	t_token	*p;

	p = *tok;
	while (p)
	{
		if (!p->next)
			return (p);
		p = p->next;
	}
	return (NULL);
}

t_token	*ps_token_list_node_create(char *s)
{
	t_token	*p;

	p = malloc(sizeof(t_token));
	if (!p)
		return (NULL);
	p->word = f_strdup(s);
	p->type = 0;
	p->quote = NONE;
	p->word_index = 0;
	p->cmd_index = 0;
	p->next = NULL;
	p->prev = NULL;
	return (p);
}

int ps_token_list_node_add(t_token **tok, t_token *new)
{
	t_token *tail;

	if (!tok || !new)
		return (-1);
	if (!tok[0] && !tok[1])
	{
		tok[0] = new;
		tok[1] = new;
	}
	else
	{
		tail = tok[1];
		tail->next = new;
		tok[1] = new;
		new->prev = tail;
	}
	return (0);
}

void ps_token_list_node_destroy(t_token **tok, t_token *del)
{
	t_token *curr;

	if (!tok || !tok[0] || !tok[1] || !del)
		return;
	curr = tok[0];
	while (curr && curr != del)
		curr = curr->next;
	if (!curr)
		return;
	if (curr->prev)
		curr->prev->next = curr->next;
	if (curr->next)
		curr->next->prev = curr->prev;
	free(curr->word);
	if (del == tok[0])
		tok[0] = curr->next;
	if (del == tok[1])
		tok[1] = curr->prev;
	free(curr);
}

void	ps_token_list_free_all(t_token **tok)
{
	if (!tok || !tok[0] || !tok[1])
		return ;
	while (tok[0])
		ps_token_list_node_destroy(tok, tok[0]);
	free(tok);
}

t_token **ps_token_list_from_array(char *s)
{

	char     buf[2];
	t_token **tok;

	if (!s || !*s)
		return (NULL);
	tok = malloc(2 * sizeof(t_token *));
	if (!tok)
		return (NULL);
	tok[0] = NULL;
	tok[1] = NULL;
	while (*s)
	{
		buf[0] = *s++;
		buf[1] = '\0';
		if (ps_token_list_node_add(tok, ps_token_list_node_create(buf)) < 0)
			return (ps_token_list_free_all(tok), NULL);
	}
	return (tok);
}

void ps_token_list_print(t_token **tok_list)
{
	t_token *tok;

	tok = *tok_list;
	printf("%-10s | %-10s | %-10s | %-10s\n", "quote", "char", "word", "cmd");
	printf("------------------------------------------\n");
	while (tok)
	{
		if (tok->word)
			printf("%-10d | %-10s | %-10ld | %-10ld\n", tok->quote, tok->word, tok->word_index, tok->cmd_index);
		tok = tok->next;
	}
	f_printf("\n");
}

/* PARSING */
static int ps_token_list_update_quote_state(char c, int state)
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

void ps_token_list_mark_quotes(t_token **tok_list)
{
	t_token *curr;
	char     c;
	int      state;

	curr = *tok_list;
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
void ps_token_list_set_index_cmd(t_token **tok_list)
{
	size_t   cmd;
	t_token *curr;

	if (!tok_list)
		return;
	cmd = 0;
	curr = *tok_list;
	while (curr)
	{
		if (curr->word[0] == '|' && curr->prev && curr->next)
			if ((f_isalnum(curr->prev->word[0]) || f_isspace(curr->prev->word[0])) && (f_isalnum(curr->next->word[0]) || f_isspace(curr->prev->word[0])))
				cmd++;
		curr->cmd_index = cmd;
		curr = curr->next;
	}
}

/* FIXME: cmd >| file should treat >| as one word */
void ps_token_list_set_index_word(t_token **tok_list)
{
	size_t   word;
	t_token *curr;
	bool     sep;

	if (!tok_list)
		return;
	word = 0;
	sep = false;
	curr = *tok_list;
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

/* Update index to separate construct of the form >file into two words */
void ps_token_list_update_indices(t_token **tok_list)
{
	char     c;
	size_t   i;
	t_token *curr;

	if (!tok_list)
		return;
	i = 0;
	curr = *tok_list;
	while (curr)
	{
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

void ps_token_list_delete_unquoted_spaces(t_token **tok_list)
{
	t_token *next;
	t_token *curr;

	if (!tok_list)
		return;
	curr = *tok_list;
	while (curr)
	{
		next = curr->next;
		if (curr->quote == NONE && f_isspace(curr->word[0]))
			ps_token_list_node_destroy(tok_list, curr);
		curr = next;
	}
}

/* FIXME: Make the function shorter */
void ps_token_list_delete_unquoted_quotes(t_token **tok_list)
{
	t_token *next;
	t_token *curr;

	if (!tok_list)
		return;
	curr = *tok_list;
	while (curr)
	{
		next = curr->next;
		if (curr->quote == NONE && (curr->word[0] == '\'' || curr->word[0] == '"'))
		{
			if (next && (next->word[0] == curr->word[0]))
			{
				curr->word[0] = '\0';
				ps_token_list_node_destroy(tok_list, next);
				curr = curr->next;
			}
			else
			{
				ps_token_list_node_destroy(tok_list, curr);
				curr = next;
			}
		}
		else
			curr = curr->next;
	}
}

/* FIXME: Do not delete || */
void ps_token_list_delete_unquoted_pipes(t_token **tok_list)
{
	t_token *next;
	t_token *curr;

	if (!tok_list)
		return;
	curr = *tok_list;
	while (curr)
	{
		next = curr->next;
		if (curr->quote == NONE && curr->word[0] == '|')
			ps_token_list_node_destroy(tok_list, curr);
		curr = next;
	}
}

void ps_token_list_recreate_words(t_token **tok_list)
{
	char    *tmp;
	t_token *curr;
	t_token *next;

	if (!tok_list || !*tok_list)
		return;
	curr = *tok_list;
	next = curr->next;
	while (curr)
	{
		next = curr->next;
		while (next && (curr->word_index == next->word_index))
		{
			tmp = f_strjoin(curr->word, next->word);
			free(curr->word);
			curr->word = tmp;
			ps_token_list_node_destroy(tok_list, next);
			next = curr->next;
		}
		curr = curr->next;
	}
}

static bool ps_line_has_balanced_quotes(char *s)
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

static int ps_token_list_process_characters(t_token **tok)
{
	ps_token_list_mark_quotes(tok);
	ps_token_list_set_index_word(tok);
	ps_token_list_set_index_cmd(tok);
	ps_token_list_delete_unquoted_spaces(tok);
	ps_token_list_delete_unquoted_quotes(tok);
	ps_token_list_update_indices(tok);
	ps_token_list_delete_unquoted_pipes(tok);
	ps_token_list_recreate_words(tok);
	ps_token_list_print(tok);
	return (0);
}

t_token **parsing(char *buf)
{
	t_token **tok;

	if (!ps_line_has_balanced_quotes(buf))
		printf("minishell: syntax error.\n");
	else
	{
		tok = ps_token_list_from_array(buf);
		if (!tok)
			return (NULL);
		ps_token_list_process_characters(tok);
	}
	return (tok);
}

//int main(const int ac, const char *av[], const char *ep[])
//{
//	(void) ac;
//	(void) av;
//	(void) ep;
//	t_token **tok;
//	char    *buf;
//
//	while (1)
//	{
//		buf = readline("MS $ ");
//		if (!buf || !*buf)
//			continue;
//		tok = parsing(buf);
//		ps_token_list_free_all(tok);
//		free(buf);
//	}
//	return (EXIT_SUCCESS);
//}
