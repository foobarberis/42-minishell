#include "minishell.h"

static void blt_export__sort(t_env **arr)
{
	size_t i;
	t_env *tmp;

	i = 0;
	while (arr[i] && arr[i + 1])
	{
		if (arr[i + 1] && (f_strcmp(arr[i]->key, arr[i + 1]->key) > 0))
		{
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
}

static t_env **blt_export__copy_sort(t_glb *glb)
{
	size_t i;
	t_env **arr;
	t_env *curr;

	curr = *(glb->env);
	i = env_list_get_size(glb->env);
	arr = malloc((i + 1) * sizeof(t_env *));
	if (!arr)
		panic(glb, CODE_MALLOC);
	arr[i] = NULL;
	i = 0;
	while (curr)
	{
		arr[i++] = curr;
		curr = curr->next;
	}
	blt_export__sort(arr);
	return (arr);
}

static void blt_export__print(t_glb *glb)
{
	size_t i;
	t_env **arr;

	i = 0;
	arr = blt_export__copy_sort(glb);
	while (arr[i])
	{
		if (arr[i]->value)
			printf("declare -x %s=\"%s\"\n", arr[i]->key, arr[i]->value);
		else
			printf("declare -x %s\n", arr[i]->key);
		i++;
	}
	free(arr);
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

	i = 1;
	while (argv[i])
		env_list_key_del(glb, argv[i++]);
	return (0);
}
