#include "minishell.h"

int ps_token_list_check_for_null(t_token **tok)
{
	t_token *curr;

	curr = *tok;
	while (curr)
	{
		if (!curr->word)
			return (1);
		curr = curr->next;
	}
	return (0);
}
