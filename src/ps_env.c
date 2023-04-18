#include "minishell.h"

// gcc -Wall -Wextra -g3 -fsanitize=address ps_env.c ../mlc/libft.a -I../inc -I../mlc/inc

static size_t env_get_key_len(char *s)
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

static char *env_search_key(char **envp, char *s)
{
	size_t tmp_len;
	size_t key_len;

	key_len = env_get_key_len(s);
	while (*envp)
	{
		tmp_len = env_get_key_len(*envp);
		if ((key_len == tmp_len) && (**envp == *s))
			if (!f_memcmp(*envp, s, key_len))
				return (*envp);
		envp++;
	}
	return (NULL);
}

t_env *env_init(char **envp)
{
	size_t i;
	t_env *p;

	i = 0;
	p = malloc(sizeof(t_env));
	if (!p)
		return (NULL);
	p->envp = envp;
	while (envp[i])
		i++;
	i += 1; /* add 1 to account for the NULL string */
	p->size = i;
	return (p);
}
/**
 * @brief Add a new key/value pair to the environment. If the key exists
 * already, updates the value.
 * @param envp The array of strings containing the environment.
 * @param s The string containing the key/value pair.
 */
void env_export(char **envp, char *s)
{
	char *p;

	p = env_search_key(envp, s);
	if (p)
	{
		p = f_strdup(s);
		return;
	}
}

void env_unset(char **envp, char *s)
{

}

int main(int argc, char *argv[], char *envp[])
{
	t_env *env;

	env = env_init(envp);
	if (!env)
		return (EXIT_FAILURE);
	char *key="SHELL";
	env_export(env->envp, "SHELL=test");
	char *tmp = env_search_key(env->envp, key);
	f_printf("%s\n", tmp);
}
