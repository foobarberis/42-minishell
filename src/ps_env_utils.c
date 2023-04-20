#include "minishell.h"

size_t env_key_get_len(char *s)
{
	size_t key_len;

	key_len = 0;
	if (!s)
		return (0);
	while (*s && *s != '=')
	{
		s++;
		key_len++;
	}
	return (key_len);
}

int env_key_search(t_env *env, char *s)
{
	int    pos;
	size_t tmp_len;
	size_t key_len;

	pos = 0;
	key_len = env_key_get_len(s);
	while (env->envp[pos])
	{
		tmp_len = env_key_get_len(env->envp[pos]);
		if ((key_len == tmp_len) && (env->envp[pos][0] == *s))
			if (!f_memcmp(env->envp[pos], s, key_len))
				return (pos);
		pos++;
	}
	return (-1);
}

int env_key_add(t_env *env, char *key)
{
	char **new;

	new = env_array_dup(env->envp, env->size + 2);
	if (!new)
		return (1);
	new[env->size] = f_strdup(key);
	new[env->size + 1] = NULL;
	env_array_free(env->envp, env->size);
	env->envp = new;
	env->size += 1;
	return (0);
}

int env_key_del(t_env *env, int pos)
{
	int i;
	int j;
	char **new;

	i = 0;
	j = 0;
	new = malloc((env->size) * sizeof(char *));
	if (!new)
		return (1);
	while (env->envp[i] && (size_t) j < env->size)
	{
		if (i == pos)
		{
			i++;
			continue;
		}
		new[j++] = f_strdup(env->envp[i++]);
		if (!new[j - 1])
			return (env_array_free(new, j), 1);
	}
	env->size -= 1;
	new[j] = NULL;
	env_array_free(env->envp, env->size);
	env->envp = new;
	return (0);
}

t_env *env_init(char **envp)
{
	size_t i;
	t_env *p;

	i = 0;
	p = malloc(sizeof(t_env));
	if (!p)
		return (NULL);
	while (envp[i])
		i++;
	p->size = i;
	p->envp = env_array_dup(envp, i);
	if (!p->envp)
		return (NULL);
	return (p);
}
