#include "minishell.h"

int blt_env(t_glb *glb)
{
	t_env *curr;

	curr = *(glb->env);
	while (curr)
	{
		if (curr->value)
			printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	return (0);
}
