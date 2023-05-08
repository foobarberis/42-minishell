#include "minishell.h"

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
