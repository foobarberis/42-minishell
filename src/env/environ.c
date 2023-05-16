/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:41:39 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/16 14:00:59 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 && *s2 && (*s1 != '=' && *s2 != '='))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

size_t env_array_get_size(char **env)
{
	size_t i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void env_array_destroy(char **env, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
		free(env[i++]);
	free(env);
}

/**
 * @brief This function creates a copy of the array env.
 * @param env The array of strings to copy.
 * @param size The size of the new array.
 * @return
 */
char **env_array_realloc(char **env, size_t size)
{
	size_t i;
	char **new;

	i = 0;
	new = f_calloc(size + 1, sizeof(char *));
	if (!new)
		return (NULL);
	while (env[i] && i < size)
	{
		new[i] = f_strdup(env[i]);
		if (!new[i])
			return (env_array_destroy(new, i), NULL);
		i++;
	}
	return (new);
}

char *env_getenv(char **env, char *s)
{
	char *p;
	int pos;

	pos = env_key_search(env, s);
	if (pos == -1)
		return (NULL);
	p = f_strchr(env[pos], '=');
	p += 1;
	return (p);
}

int env_key_search(char **env, char *key)
{
	int    pos;

	pos = 0;
	while (env[pos])
	{
		if (env_strcmp(key, env[pos]))
			return (pos);
		pos++;
	}
	return (-1);
}

/**
 * @brief Add a key to the environment. Key must be of the form 'key=value'
 * or 'key=' or 'key'.
 * @param glb
 * @param key
 * @return
 */
int env_key_add(t_glb *glb, char *key)
{
	int pos;
	char **new;
	size_t size;

	pos = env_key_search(glb->env, key);
	if (pos != -1)
		return (free(glb->env[pos]), glb->env[pos] = key, 1);
	size = env_array_get_size(glb->env) + 1;
	new = env_array_realloc(glb->env, size); /* FIXME: Add panic if NULL */
	env_array_destroy(glb->env, env_array_get_size(glb->env));
	if (!new)
		return (1);
	new[size] = f_strdup(key);
	glb->env = new;
	return (0);
}

/**
 * @brief Remove a key from the environment. Key must be of the form 'key'.
 * @param glb
 * @param key
 * @return
 */
void env_key_del(t_glb *glb, char *key)
{
	int pos;

	pos = env_key_search(glb->env, key);
	if (pos == -1)
		return;
	free(glb->env[pos]);
	while (glb->env[pos])
	{
		glb->env[pos] = glb->env[pos + 1];
		pos++;
	}
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

// clang -Wall -Wextra -fsanitize=address,undefined env_list_utils.c ../../mlc/libft.a -I../../inc/ -I../../mlc/inc
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_glb *glb;

	glb = malloc(sizeof(glb));
	glb->env = env_array_realloc(envp, env_array_get_size(envp));
	env_array_print(glb->env);
	env_key_del(glb, "USER");
	printf("\n\n");
	env_array_print(glb->env);
}
