#include "minishell.h"

void blt_env(t_glb *glb)
{
	int i;

	i = 0;
	g_rval = 0;
	while (glb->env[i])
	{
		if (f_strchr(glb->env[i], '='))
			printf("%s\n", glb->env[i]);
		i++;
	}
}
