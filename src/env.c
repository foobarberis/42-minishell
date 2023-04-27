#include "minishell.h"

/* gcc -g3 -fsanitize=address ps_env.c ps_env_utils.c ../mlc/libft.a -I../inc -I../mlc/inc */

/* TODO: Add function to extract the value part of for a given key (for variable expansion during parsing) */
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
char *env_extract_value(t_env *env, char *s)
{
	char *p;
	int pos;

	pos = env_key_search(env, s);
	if (pos == -1)
		return (NULL);
	p = env->envp[pos];
	while (*p && *p != '=')
		p++;
	p += 1;
	return (p);
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

int env_export(t_env *env, char *s)
{
	int pos;

	if (!env || !env->envp || !s)
		return (0);
	pos = env_key_search(env, s);
	if (pos != -1)
		return (free(env->envp[pos]), env->envp[pos] = f_strdup(s), 0);
	else
		return (env_key_add(env, s));
}

int env_unset(t_env *env, char *s)
{
	int pos;

	if (!env || !env->envp || !s)
		return (0);
	pos = env_key_search(env, s);
	if (pos == -1)
		return (0);
	return (env_key_del(env, pos));
}

void env_array_free(char **envp, size_t size)
{
	size_t i;

	i = 0;
	if (!envp)
		return;
	while (i <= size && envp[i])
	{
		free(envp[i]);
		envp[i] = NULL;
		i++;
	}
	free(envp);
	envp = NULL;
}

/**
 * @brief Prints the environment variable, but ignore entries which do not
 * contain a '='.
 */
void env_array_print(t_env *env)
{
	size_t i;

	i = 0;
	while (env->envp[i])
	{
		if (f_memchr(env->envp[i], '=', f_strlen(env->envp[i])))
			f_printf("%s\n", env->envp[i]);
		i++;
	}
}

char **env_array_dup(char **envp, size_t size)
{
	size_t i;
	char **new;

	i = 0;
	new = malloc((size + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (envp[i] && i < size)
	{
		new[i] = f_strdup(envp[i]);
		if (!new[i])
			return (env_array_free(new, i), NULL);
		i++;
	}
	return (new[i] = NULL, new);
}

// int main(int ac, char *av[], char *ep[])
// {
// 	(void) ac;
// 	(void) av;
// 	t_env *env;

// 	env = env_init(ep);
// 	env_extract_value(env, "USER");
// 	env_array_free(env->envp, env->size);
// 	free(env);
// }


/* int main(int ac, char *av[], char *ep[])
{
	(void) ac;
	(void) av;
	t_env *env;

	f_printf("\n--- ORIGINAL ---\n");
	for (int i = 0; ep[i]; i++)
		printf("%s\n", ep[i]);
	env = env_init(ep);
	if (!env)
		return (EXIT_FAILURE);
	f_printf("\n--- EXPORT ---\n");
	env_export(env, "coucou=hello");
	env_array_print(env);
	f_printf("\n--- UNSET ---\n");
	env_unset(env, "coucou");
	env_array_print(env);
	env_array_free(env->envp, env->size);
	free(env);
} */
