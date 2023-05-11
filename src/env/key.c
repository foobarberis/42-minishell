#include "minishell.h"

static int env_list_key_add__add(t_glb *glb, char *key, char *value)
{
	t_env *tmp;

	tmp = env_list_node_create(key, value);
	if (!tmp)
	{
		free(key);
		free(value);
		panic(glb, CODE_MALLOC);
	}
	env_list_node_add(glb->env, tmp);
	return (0);
}

void  env_list_key_add(t_glb *glb, char *key)
{
	t_env *curr;
	char  *tmp[2];

	tmp[0] = NULL;
	tmp[1] = NULL;
	if (env_split_key_value(tmp, key))
		return;
	curr = env_list_key_search(glb->env, tmp[0]);
	if (curr)
	{
		if (curr->value)
			free(curr->value);
		curr->value = tmp[1];
		free(tmp[0]);
	}
	else
		env_list_key_add__add(glb, tmp[0], tmp[1]);
	env_envp_update(glb);
}

void env_list_key_del(t_glb *glb, char *key)
{
	t_env *curr;

	curr = env_list_key_search(glb->env, key);
	if (curr)
	{
		env_list_node_rm(glb->env, curr);
		env_envp_update(glb);
	}
}

/* If the key is found, return the associated value. If not found, return the empty string. */
char *env_getenv(t_env **env, const char *key)
{
	t_env *curr;

	curr = *env;
	while (curr)
	{
		if (curr->key && !f_strcmp(key, curr->key))
			return (f_strdup(curr->value));
		curr = curr->next;
	}
	return (f_strdup(""));
}
