#include "minishell.h"

//WARNING: Quoted vs unquoted here-doc limiter

// Steps:
// - Mark quote state
// - Delete unquoted quotes
// - Attribute index to letter who belong in the same word
// 		- Separate construct of the form >file or <file into > file or < file
// - Attribute index to the letters who belongs to the same command
// - Delete all unquoted spaces
// - Look for syntax error e.g 'MSH $ | grep', 'MSH $ ''', 'MSH $ ""'
// - Delete unquoted quotes and unquoted pipes
	// - WARNING: MS $ '' should produce an empty string not an empty list
// - Reassemble words
// - Expand variables
// - Turn consecutive words with the same quote state into one string
// - Fill in type information
// - Error checking i.e open file, check if prog exists and so on
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

void ps_token_list_mark_quotes(t_token *tok)
{
	char c;
	int  state;

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

void ps_token_list_mark_indices(t_token *tok)
{
	bool   was_space;
	size_t word;
	size_t cmd;

	word = 0;
	cmd = 0;
	was_space = false;
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
		tok->wnum = word;
		tok->cmdnum = cmd;
		tok = tok->next;
	}
}

void ps_token_list_delete_unquoted_spaces(t_token *tok)
{
	if (!tok)
		return ;
	while (tok)
	{
		if (tok->quote == NONE && f_isspace(tok->word[0]))
			tok = ps_token_list_node_destroy(tok);
		if (tok)
			tok = tok->next;
	}
}

// WARNING: When deleting quotes, if curr == '"' && next == '"' it should
// be replaced by one block with word set to the empty string
/* void ps_token_list_delete_unquoted(t_token *tok)
{
	t_token *tmp;
	char     curr;

	tmp = tok;
	while (tmp)
	{
		curr = tmp->word[0];
		if (tmp->quote == NONE && (f_isspace(curr) || curr == '\'' || curr == '"' || curr == '|'))
			tmp = ps_token_list_node_destroy(tmp);
		if (tmp)
			tmp = tmp->next;
	}
} */
