#include "minishell.h"

static void env_key_del_plus(char *s)
{
	char *p;

	p = f_strchr(s, '+');
	if (!p || (*(p + 1) != '='))
		return;
	while (*p)
	{
		*p = *(p + 1);
		p++;
	}
}

static char **env_key_modify(char **env, char *key, int pos)
{
	char *p;
	char *new;

	p = f_strchr(key, '+');
	if (!p)
		return (free(env[pos]), env[pos] = key, env);
	else
	{
		new = f_strjoin(env[pos], p + 2);
		if (!new)
			return (env_array_destroy(env, env_array_get_size(env)), free(key), NULL);
		return (free(env[pos]), env[pos] = new, env);
	}
	return (env);
}

char	**env_key_add(char **env, char *key)
{
	int		pos;
	char	**new;
	size_t	size;

	if (env && !key)
		return (env_array_destroy(env, env_array_get_size(env)), NULL);
	pos = env_key_get_pos(env, key);
	if (pos != KEY_NOT_FOUND)
		return (env_key_modify(env, key, pos));
	env_key_del_plus(key);
	/* If key was not found but contains a '+' remove it before adding */
	size = env_array_get_size(env) + 1;
	new = env_array_realloc(env, size);
	if (!new)
		return (env_array_destroy(env, env_array_get_size(env)), free(key),
			NULL);
	env_array_destroy(env, env_array_get_size(env));
	new[size - 1] = key;
	return (new);
}
