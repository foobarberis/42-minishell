#include "minishell.h"

// FIXME: Print as in Bash i.e "declare -x key=value" and sort in ASCII order

void blt_export__array_print(t_env *env)
{
	// duplicate array
	// sort the duplicate
	// print the sorted array and add "declare -x" before each key=value + add "" arround the value
	// free the sorted array
}

// WARNING: When doing "export TEST", TEST does not show up in env but does
// show up in export.
int blt_export(t_glb *glb, char *key)
{
	if (!key)
		return (env_array_print(glb->env), 0);
	else
		return (env_export(glb->env, key));
}

int blt_unset(t_glb *glb, char *key)
{
	if (!key)
		return (0);
	return (env_unset(glb->env, key));
}
