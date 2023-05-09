#include "minishell.h"

/* FIXME: Print as in Bash i.e "declare -x key=value" and sort in ASCII order */
static void blt_export__print(t_env **env)
{
	t_env *curr;

	if (!env || !*env)
		return;
	curr = *env;
	while (curr)
	{
		if (curr->value)
			f_printf("declare -x %s=\"%s\"\n", curr->key, curr->value);
		curr = curr->next;
	}
}

/* https://www.gnu.org/software/bash/manual/html_node/Bourne-Shell-Builtins.html#index-export */
int blt_export(t_glb *glb, char **argv)
{
	size_t i;

	if (!glb || !argv)
		return (0);
	i = 1;
	if (!argv[1]) /* if export was not given any arg, print all env variables */
		return (blt_export__print(glb->env), 0);
	while (argv[i])
	{
		if (!env_list_is_valid_id(argv[i]))
			return (f_perror(ERR_ID), 1);
		else
			env_list_key_add(glb, argv[i]);
		i++;
	}
	return (0);
}

/* https://www.gnu.org/software/bash/manual/html_node/Bourne-Shell-Builtins.html#index-unset */
int blt_unset(t_glb *glb, char **argv)
{
	size_t i;

	if (!glb || !argv)
		return (0);
	i = 0;
	while (argv[i])
		env_list_key_del(glb, argv[i++]);
	return (0);
}
