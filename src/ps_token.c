#include "minishell.h"

//WARNING: Quoted vs unquoted here-doc limiter

// Steps:
// - Mark quote state
// - Delete unquoted quotes
// - Attribute index to letter who belong in the same word
// 		- Separate construct of the form >file or <file into > file or < file
// - Delete all unquoted spaces and unquoted quotes
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

void ps_token_list_give_index(t_token *tok)
{
	char c;
	bool was_space;
	size_t i;

	i = 0;
	while (tok)
	{
		c = tok->word[0];
		if (f_isspace(c) && !was_space)
		{
			was_space = true;
			i++;
		}
		tok->index = i;
		tok = tok->next;
	}
}

void ps_token_list_delete_unquoted_spaces(t_token *tok)
{
	t_token *del;
	char     curr;

	while (tok)
	{
		curr = tok->word[0];
		if (tok->quote == NONE && f_isspace(curr))
		{
			del = tok;
			ps_token_list_node_destroy(del);
		}
		tok = tok->next;
	}
}
