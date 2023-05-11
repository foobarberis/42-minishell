#include "minishell.h"

bool env_list_is_valid_id(char *s)
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

int env_split_key_value(char **arr, char *s)
{
	char *p;
	char *q;

	p = f_strdup(s);
	if (!p)
		return (1);
	q = f_strchr(p, '=');
	if (q)
		*q++ = 0;
	arr[0] = f_strdup(p);
	if (!arr[0])
		return (free(p), 1);
	arr[1] = f_strdup(q);
	if (!arr[1])
		return (free(arr[0]), free(p), 1);
	free(p);
	return (0);
}

void env_list_print(t_env **env)
{
	t_env *curr;

	curr = *env;
	while (curr)
	{
		if (curr->value)
			f_printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}

void env_list_from_array(t_glb *glb, char **ep)
{
	t_env *tmp;
	char  *arr[2];

	while (*ep)
	{
		arr[0] = NULL;
		arr[1] = NULL;
		if (env_split_key_value(arr, *ep))
			panic(glb, CODE_MALLOC);
		tmp = env_list_node_create(arr[0], arr[1]);
		if (!tmp)
		{
			free(arr[0]);
			free(arr[1]);
			panic(glb, CODE_MALLOC);
		}
		env_list_node_add(glb->env, tmp);
		ep++;
	}
}

t_env *env_list_key_search(t_env **env, char *key)
{
	t_env *curr;

	curr = *env;
	while (curr)
	{
		if (curr->key && !f_strcmp(curr->key, key))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
