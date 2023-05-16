/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:41:39 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/16 16:17:30 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *env_getenv(char **env, char *s)
{
	char *p;
	int pos;

	pos = env_key_get_pos(env, s);
	if (pos == KEY_NOT_FOUND)
		return (NULL);
	p = f_strchr(env[pos], '=');
	if (p)
		return (++p);
	return (env[pos] + f_strlen(env[pos]));
}

int env_key_add(t_glb *glb, char *key)
{
	int pos;
	char **new;
	char *s;
	size_t size;

	s = f_strdup(key);
	if (!s)
		return (panic(glb, CODE_MALLOC), 1);
	pos = env_key_get_pos(glb->env, key);
	if (pos != KEY_NOT_FOUND)
		return (free(glb->env[pos]), glb->env[pos] = s, 1);
	size = env_array_get_size(glb->env) + 1;
	new = env_array_realloc(glb->env, size);
	if (!new)
		return (free(s), panic(glb, CODE_MALLOC), 1);
	env_array_destroy(glb->env, env_array_get_size(glb->env));
	new[size - 1] = s;
	glb->env = new;
	return (0);
}

/**
 * @brief Remove a key from the environment. Key must be of the form 'key'.
 */
void env_key_del(t_glb *glb, char *key)
{
	int pos;

	pos = env_key_get_pos(glb->env, key);
	if (pos == KEY_NOT_FOUND)
		return;
	free(glb->env[pos]);
	while (glb->env[pos])
	{
		glb->env[pos] = glb->env[pos + 1];
		pos++;
	}
}

void env_array_print(char **env)
{
	size_t i;

	i = 0;
	while (env[i])
		f_printf("%s\n", env[i++]);
}

// clang -g3 -Wall -Wextra -fsanitize=address,undefined environ.c environ_utils.c ../../mlc/libft.a -I../../inc/ -I../../mlc/inc
/* int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_glb *glb;

	glb = malloc(sizeof(glb));
	glb->env = env_array_realloc(envp, env_array_get_size(envp));
	env_array_print(glb->env);
} */
