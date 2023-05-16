#include "minishell.h"

bool	env_is_valid_id(char *s)
{
	if (!*s)
		return (false);
	if (f_isdigit(s[0]))
		return (false);
	while (*s && *s != '=')
	{
		if (!(f_isalnum(*s) || *s == '_'))
			return (false);
		s++;
	}
	return (true);
}

static void blt_export__sort(char **arr)
{
	int i;
	char *tmp;

	i = 0;
	while (arr[i] && arr[i + 1])
	{
		if (arr[i + 1] && (env_strcmp(arr[i], arr[i + 1]) > 0))
		{
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
}

static char **blt_export__copy_sort(t_glb *glb)
{
	int i;
	char **new;

	i = 0;
	new = f_calloc(env_array_get_size(glb->env) + 1, sizeof(char *));
	if (!new)
		panic(glb, CODE_MALLOC);
	while (glb->env[i])
	{
		new[i] = glb->env[i];
		i++;
	}
	blt_export__sort(new);
	return (new);
}

static void blt_export__print(t_glb *glb)
{
	int i;
	char *p;
	char **new;

	i = 0;
	new = blt_export__copy_sort(glb);
	while (new[i])
	{
		p = f_strchr(new[i], '=');
		if (p)
		{
			*p = 0;
			printf("declare -x %s=\"%s\"\n", new[i], p + 1);
			*p = '=';
		}
		else
			printf("declare -x %s\n", new[i]);
		i++;
	}
	free(new);
}

/* https://www.gnu.org/software/bash/manual/html_node/Bourne-Shell-Builtins.html#index-export */
int blt_export(t_glb *glb, char **argv)
{
	size_t i;

	i = 1;
	if (!argv || !argv[1])
		return (0);
	if (!argv[1][0])
		return (blt_export__print(glb), 0);
	while (argv[i])
	{
		if (!env_is_valid_id(argv[i]))
			return (f_dprintf(STDERR_FILENO, "minishell: export: `%s': not a valid identifier"), g_rval = 1, 1);
		env_key_add(glb, argv[i]);
		i++;
	}
	return (g_rval = 0, 0);
}

/* https://www.gnu.org/software/bash/manual/html_node/Bourne-Shell-Builtins.html#index-unset */
int blt_unset(t_glb *glb, char **argv)
{
	size_t i;

	i = 1;
	while (argv[i])
		env_key_del(glb, argv[i++]); /* WARNING: Must match the key and only the key, i.e unset("SHELL") is ok but unset("SHELL=/bin/bash") should do nothing */
	return (g_rval = 0, 0);
}
