#include "minishell.h"

size_t env_list_get_size(t_env **env)
{
	size_t i;
	t_env *curr;

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

	p = f_strjoin(node->key, "="); /* FIXME: Error checking */
	if (!p)
		return (NULL);
	q = f_strjoin(p, node->value); /* FIXME: Error checking */
	return (free(p), q);
}

/* This function free's char **envp */
void env_environ_free(char **envp)
{
	size_t i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

/* FIXME: Error checking */
void env_envp_update(t_glb *glb)
{
	char **new;
	size_t i;
	t_env *curr;

	i = env_list_get_size(glb->env);
	new = malloc((i + 1) * sizeof(char *));
	if (!new)
		panic(glb, CODE_MALLOC);
	new[i] = NULL;
	i = 0;
	curr = glb->env[0];
	while (curr)
	{
		new[i] = env_join_key_value(curr);
		if (!new[i++])
			return (env_environ_free(new), panic(glb, CODE_MALLOC));
		curr = curr->next;
	}
	if (glb->environ)
		env_environ_free(glb->environ);
	glb->environ = new;
}
