#include "minishell.h"

t_env *env_list_node_create(char *key, char *value)
{
	t_env *new;

	if (!key || !value)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void env_list_node_destroy(t_env *node)
{
	if (!node)
		return;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void env_list_node_add(t_env **env, t_env *node)
{
	t_env *last;

	if (!env || !node)
		return;
	if (!*env)
		*env = node;
	else
	{
		last = env_list_goto_last(env);
		if (last)
			last->next = node;
	}
}

void env_list_node_rm(t_env **env, t_env *node)
{
	t_env *curr;
	t_env *next;

	if (!env || !node)
		return;
	curr = *env;
	while (curr)
	{
		next = curr->next;
		if (next == node)
		{
			if (env[0] == node)
				env[0] = env[0]->next;
			curr->next = next->next;
			return (env_list_node_destroy(next));
		}
		curr = next;
	}
}

void env_list_free_all(t_env **env)
{
	t_env *curr;
	t_env *next;

	if (!env)
		return;
	curr = *env;
	while (curr)
	{
		next = curr->next;
		env_list_node_destroy(curr);
		curr = next;
	}
}

t_env *env_list_goto_last(t_env **env)
{
	t_env *curr;

	if (!env)
		return (NULL);
	curr = *env;
	while (curr)
	{
		if (!curr->next)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

size_t env_list_get_size(t_env **env)
{
	size_t i;
	t_env *curr;

	if (!env)
		return (0);
	i = 0;
	curr = *env;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}
