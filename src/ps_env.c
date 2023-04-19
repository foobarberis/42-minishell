#include "minishell.h"

/* gcc -g3 -fsanitize=address ps_env.c ps_env_utils.c ../mlc/libft.a -I../inc -I../mlc/inc */

// TODO Cleanup and error checking

/**
 * @brief Add a new key/value pair to the environment. If the key exists
 * already, updates the value.
 * @param envp The array of strings containing the environment.
 * @param s The string containing the key/value pair.
 */
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

int main(int ac, char *av[], char *ep[])
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
}
