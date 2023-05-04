#include "minishell.h"

t_token *ps_token_list_goto_last(t_token **tok)
{
	t_token *curr;

	curr = *tok;
	while (curr)
	{
		if (!curr->next)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

t_token *ps_token_list_node_create(char *s)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->word = f_strdup(s);
	if (!new->word)
		return (NULL);
	new->type = BASIC;
	new->quote = NONE;
	new->word_index = 0;
	new->cmd_index = 0;
	new->next = NULL;
	return (new);
}

int ps_token_list_node_add(t_token **tok, t_token *new)
{
	t_token *tail;

	if (!tok || !new)
		return (1);
	if (!*tok)
		*tok = new;
	else
	{
		tail = ps_token_list_goto_last(tok);
		if (tail)
			tail->next = new;
	}
	return (0);
}

/* a[0] -> curr, a[1] -> curr->next, a[2] -> curr->next->next */
void ps_token_list_node_destroy(t_token **tok, t_token *del)
{
	t_token *a[3];

	if (!tok || !*tok || !del)
		return;
	a[0] = *tok;
	if (a[0] == del)
	{
		a[1] = a[0]->next;
		free(a[0]->word);
		free(a[0]);
		*tok = a[1];
		return;
	}
	while (a[0] && a[1])
	{
		a[1] = a[0]->next;
		if (a[1])
			a[2] = a[1]->next;
		if (a[1] == del)
		{
			free(a[1]->word);
			free(a[1]);
			a[0]->next = a[2];
			return;
		}
		a[0] = a[1];
	}
}

void ps_token_list_free_all(t_token **tok)
{
	if (!tok || !tok[0] || !tok[1])
		return;
	while (tok[0])
		ps_token_list_node_destroy(tok, tok[0]);
	free(tok);
}

t_token **ps_token_list_from_array(char *s)
{
	char      buf[2];
	t_token **tok;

	if (!s || !*s)
		return (NULL);
	tok = malloc(sizeof(t_token *));
	if (!tok)
		return (NULL);
	tok[0] = NULL;
	buf[1] = '\0';
	while (*s)
	{
		buf[0] = *s++;
		if (ps_token_list_node_add(tok, ps_token_list_node_create(buf)))
			return (ps_token_list_free_all(tok), NULL);
	}
	return (tok);
}
