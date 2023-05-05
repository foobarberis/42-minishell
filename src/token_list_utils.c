#include "minishell.h"

t_token *ps_token_list_node_create(char *s)
{
	t_token *new;

	if (!s)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->word = f_strdup(s);
	if (!new->word)
		return (free(new), NULL);
	new->type = BASIC;
	new->quote = NONE;
	new->word_index = 0;
	new->cmd_index = 0;
	new->next = NULL;
	return (new);
}

void ps_token_list_node_destroy(t_token *node)
{
	if (!node)
		return;
	if (node->word)
		free(node->word);
	free(node);
}

void ps_token_list_node_add(t_token **tok, t_token *node)
{
	t_token *last;

	if (!tok || !node)
		return;
	if (!*tok)
		*tok = node;
	else
	{
		last = ps_token_list_goto_last(tok);
		if (last)
			last->next = node;
	}
}

void ps_token_list_node_rm(t_token **tok, t_token *node)
{
	t_token *curr;
	t_token *next;

	if (!tok || !node)
		return;
	curr = *tok;
	while (curr)
	{
		next = curr->next;
		if (next == node)
		{
			if (tok[0] == node)
				tok[0] = tok[0]->next;
			curr->next = next->next;
			return (ps_token_list_node_destroy(next));
		}
		curr = next;
	}
}

/* WARNING: Free tok when finished */
void ps_token_list_free_all(t_token **tok)
{
	t_token *curr;
	t_token *next;

	if (!tok)
		return;
	curr = *tok;
	while (curr)
	{
		next = curr->next;
		ps_token_list_node_destroy(curr);
		curr = next;
	}
}

t_token *ps_token_list_goto_last(t_token **tok)
{
	t_token *curr;

	if (!tok)
		return (NULL);
	curr = *tok;
	while (curr)
	{
		if (!curr->next)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
