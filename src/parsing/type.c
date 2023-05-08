#include "minishell.h"

void ps_token_list_fill_type(t_token **tok)
{
	t_token *curr;

	if (!tok)
		return;
	curr = *tok;
	while (curr)
	{
		if (curr->quote == NONE)
		{
			if (!curr->next)
				break;
			if (!f_strcmp(curr->word, ">"))
				curr->next->type = S_OUTPUT;
			else if (!f_strcmp(curr->word, "<"))
				curr->next->type = S_INPUT;
			else if (!f_strcmp(curr->word, ">>"))
				curr->next->type = D_OUTPUT;
			else if (!f_strcmp(curr->word, "<<"))
				curr->next->type = D_INPUT;
		}
		curr = curr->next;
	}
}
