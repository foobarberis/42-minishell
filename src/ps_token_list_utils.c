#include "minishell.h"

t_token	*ps_token_list_goto_last(t_token *tok)
{
	t_token	*p;

	p = tok;
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
	p->next = NULL;
	p->prev = NULL;
	return (p);
}

int	ps_token_list_node_add(t_token *tok, t_token *new)
{
	t_token *p;

	if (!tok || !new)
		return (-1);
	p = ps_token_list_goto_last(tok);
	p->next = new;
	new->prev = p;
	return (0);
}

void ps_token_list_node_destroy(t_token *tok)
{
	t_token *before;
	t_token *after;

	before = tok->prev;
	after = tok->next;
	if (before)
		before->next = after;
	if (after)
		after->prev = before;
	free(tok->word);
	tok->word = NULL;
	free(tok);
	tok = NULL;
	return (before);
}

/* void ps_token_list_node_destroy(t_token *tok)
{
	t_token *before;
	t_token *after;

	before = tok->prev;
	after = tok->next;
	if (before)
		before->next = after;
	if (after)
		after->prev = before;
	free(tok->word);
	tok->word = NULL;
	free(tok);
	tok = NULL;
	return (before);
} */

void	ps_token_list_free_all(t_token *tok)
{
	t_token	*curr;
	t_token	*next;

	if (!tok)
		return ;
	curr = tok;
	while (curr)
	{
		next = curr->next;
		free(curr->word);
		curr->word = NULL;
		curr->next = NULL;
		curr->prev = NULL;
		free(curr);
		curr = next;
	}
}

t_token *ps_token_list_from_array(char *s)
{
	t_token *tok;
	char     buf[2];

	if (!s || !*s)
		return (NULL);
	buf[0] = *s++;
	buf[1] = '\0';
	tok = ps_token_list_node_create(buf);
	if (!tok)
		return (NULL);
	while (*s)
	{
		buf[0] = *s;
		buf[1] = '\0';
		if (ps_token_list_node_add(tok, ps_token_list_node_create(buf)) < 0)
			return (ps_token_list_free_all(tok), NULL);
		s++;
	}
	return (tok);
}

void ps_token_list_print(t_token *tok)
{
	while (tok)
	{
		if (tok->word && tok->quote == NONE)
			f_printf("%s", tok->word);
		tok = tok->next;
	}
	f_printf("\n");
}
