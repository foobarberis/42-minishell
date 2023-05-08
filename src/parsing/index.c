#include "minishell.h"


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
	int      state;

	if (!tok || !*tok)
		return;
	curr = *tok;
	state = NONE;
	while (curr)
	{
		if (state == NONE && (curr->word[0] == '\'' || curr->word[0] == '"'))
		{
			curr->quote = NONE;
			state = ps_token_list_update_quote_state(curr->word[0], state);
			curr = curr->next;
		}
		else
		{
			state = ps_token_list_update_quote_state(curr->word[0], state);
			curr->quote = state;
			curr = curr->next;
		}
	}
}

void ps_token_list_set_index_cmd(t_token **tok)
{
	size_t   cmd;
	t_token *curr;

	if (!tok || !*tok)
		return;
	cmd = 0;
	curr = *tok;
	while (curr)
	{
		if (curr->word[0] == '|')
			cmd++;
		curr->cmd_index = cmd;
		curr = curr->next;
	}
}

/* FIXME: In `ls |<file cat` |< should be counted as two words  */
void ps_token_list_set_index_word(t_token **tok)
{
	bool     sep;
	size_t   word;
	t_token *curr;

	if (!tok || !*tok)
		return;
	word = 0;
	sep = false;
	curr = *tok;
	while (curr)
	{
		if (ismeta(curr->word[0]) && !sep)
		{
			sep = true;
			word++;
		}
		else if (!ismeta(curr->word[0]) && sep)
		{
			sep = false;
			word++;
		}
		curr->word_index = word;
		curr = curr->next;
	}
}
