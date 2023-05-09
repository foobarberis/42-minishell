#include "minishell.h"

void ps_token_list_delete_space(t_token **tok)
{
	t_token *next;
	t_token *curr;

	if (!tok || !*tok)
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

void ps_token_list_delete_quote(t_token **tok)
{
	t_token *next;
	t_token *curr;

	if (!tok || !*tok)
		return;
	curr = *tok;
	while (curr)
	{
		next = curr->next;
		if (curr->quote == NONE && (curr->word[0] == '\'' || curr->word[0] == '"'))
			ps_token_list_node_rm(tok, curr);
		curr = next;
	}
}

void ps_token_list_delete_dollar(t_token **tok)
{
	t_token *next;
	t_token *curr;

	if (!tok || !*tok)
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

void ps_token_list_delete_bracket(t_token **tok)
{
	t_token *next;
	t_token *curr;

	if (!tok || !*tok)
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

void ps_token_list_delete_pipe(t_token **tok)
{
	t_token *next;
	t_token *curr;

	if (!tok || !*tok)
		return;
	curr = *tok;
	while (curr)
	{
		next = curr->next;
		if (next && curr->quote == NONE && curr->word[0] == '|')
			ps_token_list_node_rm(tok, curr);
		curr = next;
	}
}
