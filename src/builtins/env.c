#include "minishell.h"

int blt_env(t_glb *glb)
{
	int i;

	i = 0;
	while (glb->env[i])
	{
		if (f_strchr(glb->env[i], '='))
			printf("%s\n", glb->env[i]);
		i++;
	}
	return (0);
}
