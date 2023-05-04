#include "minishell.h"

static size_t env_get_size(char **env)
{
	size_t i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

/* TODO Cleanup and error checking */
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

/* FIXME: Check for edge cases */
char *env_extract_value(char **env, char *s)
{
	char *p;
	int pos;

	pos = env_key_search(env, s);
	if (pos == -1)
		return (NULL);
	p = env[pos];
	while (*p && *p != '=')
		p++;
	p += 1;
	return (p);
}

int env_key_search(char **env, char *s)
{
	int    pos;
	size_t tmp_len;
	size_t key_len;

	pos = 0;
	key_len = env_key_get_len(s);
	while (env[pos])
	{
		tmp_len = env_key_get_len(env[pos]);
		if ((key_len == tmp_len) && (env[pos][0] == *s))
			if (!f_memcmp(env[pos], s, key_len))
				return (pos);
		pos++;
	}
	return (-1);
}

int env_key_add(char **env, char *key)
{
	size_t size;
	char **new;

	new = env_array_create(env, size + 2);
	if (!new)
		return (1);
	new[size] = f_strdup(key);
	new[size + 1] = NULL;
	env_array_destroy(env, size);
	env = new;
	size += 1;
	return (0);
}

int env_key_del(char **env, int pos)
{
	int i;
	int j;
	char **new;

	i = 0;
	j = 0;
	new = malloc((size) * sizeof(char *));
	if (!new)
		return (1);
	while (env[i] && (size_t) j < size)
	{
		if (i == pos)
		{
			i++;
			continue;
		}
		new[j++] = f_strdup(env[i++]);
		if (!new[j - 1])
			return (env_array_destroy(new, j), 1);
	}
	size -= 1;
	new[j] = NULL;
	env_array_destroy(env, size);
	env = new;
	return (0);
}



int env_export(char **env, char *s)
{
	int pos;

	if (!env || !env || !s)
		return (0);
	pos = env_key_search(env, s);
	if (pos != -1)
		return (free(env[pos]), env[pos] = f_strdup(s), 0);
	else
		return (env_key_add(env, s));
}

int env_unset(char **env, char *s)
{
	int pos;

	if (!env || !env || !s)
		return (0);
	pos = env_key_search(env, s);
	if (pos == -1)
		return (0);
	return (env_key_del(env, pos));
}


/**
 * @brief Prints the environment variable, but ignore entries which do not
 * contain a '='.
 */
void env_array_print(char **env)
{
	size_t i;

	i = 0;
	while (env[i])
	{
		if (f_memchr(env[i], '=', f_strlen(env[i])))
			f_printf("%s\n", env[i]);
		i++;
	}
}

void env_array_destroy(char **env)
{
	size_t i;

	i = 0;
	if (!env)
		return;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
	env = NULL;
}

char **env_array_create(char **env)
{
	size_t i;
	char **new;

	i = 0;
	while (env[i])
		i++;
	new = malloc((i + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	new[i] = NULL;
	i = 0;
	while (env[i])
	{
		new[i] = f_strdup(env[i]);
		if (!new[i])
			return (env_array_destroy(new), NULL);
		i++;
	}
	return (new);
}
