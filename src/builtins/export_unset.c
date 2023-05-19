#include "minishell.h"

int blt_export(t_glb *glb, int argc, char **argv)
{
	size_t i;

	i = 1;
	if (argc == 1)
		return (blt_export__print(glb), 0);
	while (argv[i])
	{
		if (!env_is_valid_id(argv[i]))
			f_dprintf(STDERR_FILENO, "minishell: export: `%s': not a valid identifier\n", argv[i++]);
		else
		{
			glb->env = env_key_add(glb->env, f_strdup(argv[i++]));
			if (!glb->env)
				panic(glb, CODE_MALLOC, NULL);
		}
	}
	return (0);
}

int blt_unset(t_glb *glb, int argc, char **argv)
{
	size_t i;

	i = 1;
	while (argv[i])
	{
		if (f_strchr(argv[i], '='))
			i++;
		else
			env_key_del(glb->env, argv[i++]);
	}
	return (0);
}
