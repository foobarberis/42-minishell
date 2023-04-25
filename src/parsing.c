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
	t_token *tmp;

	if (!tok || !tok[0] || !tok[1] || !del)
		return;
	tmp = tok[0];
	while (tmp && tmp != del)
		tmp = tmp->next;
	if (!tmp)
		return;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	free(tmp->word);
	if (del == tok[0])
		tok[0] = tmp->next;
	if (del == tok[1])
		tok[1] = tmp->prev;
	free(tmp);
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
	printf("quote | char | word index | cmd index\n");
	printf("-------------------------------------\n");
	while (tok)
	{
		if (tok->word)
			printf("%d | %s | %ld | %ld\n", tok->quote, tok->word, tok->word_index, tok->cmd_index);
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
	t_token *tok;
	char     c;
	int      state;

	tok = *tok_list;
	state = NONE;
	while (tok)
	{
		c = tok->word[0];
		if (state == NONE && (c == '\'' || c == '"'))
		{
			tok->quote = NONE;
			state = ps_token_list_update_quote_state(c, state);
			tok = tok->next;
		}
		else
		{
			state = ps_token_list_update_quote_state(c, state);
			tok->quote = state;
			tok = tok->next;
		}
	}
}

void ps_token_list_mark_indices(t_token **tok_list)
{
	bool     was_space;
	size_t   word;
	size_t   cmd;
	t_token *tok;

	word = 0;
	cmd = 0;
	was_space = false;
	tok = *tok_list;
	while (tok)
	{
		if (tok->word[0] == '|' && tok->prev && tok->next)
			if (tok->prev->word[0] == ' ' && tok->next->word[0] == ' ')
				cmd++;
		if (f_isspace(tok->word[0]) && !was_space)
		{
			was_space = true;
			word++;
		}
		else if (!f_isspace(tok->word[0]) && was_space)
			was_space = false;
		tok->word_index = word;
		tok->cmd_index = cmd;
		tok = tok->next;
	}
}

void ps_token_list_delete_unquoted_spaces(t_token **tok_list)
{
	t_token *next;
	t_token *tok;

	if (!tok_list)
		return;
	tok = *tok_list;
	while (tok)
	{
		next = tok->next;
		if (tok->quote == NONE && f_isspace(tok->word[0]))
			ps_token_list_node_destroy(tok_list, tok);
		tok = next;
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
	ps_token_list_mark_indices(tok);
	ps_token_list_delete_unquoted_spaces(tok);
	ps_token_list_print(tok);
	return (0);
}

int main(const int ac, const char *av[], const char *ep[])
{
	(void) ac;
	(void) av;
	(void) ep;
	t_token **tok;
	char    *buf;

	while (1)
	{
		buf = readline("MS $ ");
		if (!buf || !*buf)
			continue;
		if (!ps_line_has_balanced_quotes(buf))
			printf("minishell: syntax error.\n");
		else
		{
			tok = ps_token_list_from_array(buf);
			if (!tok)
				break;
			ps_token_list_process_characters(tok);
			ps_token_list_free_all(tok);
		}
		free(buf);
	}
	return (EXIT_SUCCESS);
}
