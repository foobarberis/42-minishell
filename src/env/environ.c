#include "minishell.h"

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

char *env_join_key_value(t_env *node)
{
	char *p;
	char *q;

	if (!node || !node->key || !node->value)
		return (NULL);
	p = f_strjoin(node->key, "="); /* FIXME: Error checking */
	if (!p)
		return (NULL);
	q = f_strjoin(p, node->value); /* FIXME: Error checking */
	return (free(p), q);
}

void env_envp_del(char **envp)
{
	size_t i;

	if (!envp)
		return;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

/* FIXME: Error checking */
int env_envp_update(t_glb *glb)
{
	char **new;
	size_t i;
	t_env *curr;

	if (!glb)
		return (0);
	env_envp_del(glb->ep);
	i = env_list_get_size(glb->env);
	new = malloc((i + 1) * sizeof(char *));
	glb->ep = new;
	if (!new)
		return (1);
	new[i] = NULL;
	i = 0;
	curr = glb->env[0];
	while (curr)
	{
		new[i] = NULL; // env_join_key_value(curr); /* FIXME: Error checking */
		if (!new[i])
			return (env_envp_del(new), 1);
		curr = curr->next;
	}
	return (0);
}
