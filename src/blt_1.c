#include "minishell.h"

// FIXME: Print as in Bash i.e "declare -x key=value" and sort in ASCII order
void blt_export(t_glb *glb, char *key)
{
	if (!key)
		env_array_print(glb->env);
	else
		env_export(glb->env, key);
}

void blt_unset(t_glb *glb, char *key)
{
	if (!key)
		return;
	env_unset(glb->env, key);
}
