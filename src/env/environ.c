/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:41:39 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/17 13:28:33 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **env_init_base(char *path)
{
	char **new;

	new = f_calloc(4, sizeof(char *));
	if (!new)
		return (NULL);
	new[0] = f_strjoin("PWD=", path);
	if (!new[0])
		return (free(new), NULL);
	new[1] = f_strdup("SHLVL=1");
	if (!new[1])
		return (free(new[0]), free(new), NULL);
	new[2] = f_strdup("_=/usr/bin/env");
	if (!new[2])
		return (free(new[0]), free(new[1]), free(new), NULL);
	return (new);
}

char **env_init(char **envp)
{
	char path[PATH_MAX];

	if (!getcwd(path, PATH_MAX))
		return (perror("minishell: getcwd: "), NULL);
	if (!envp[0])
		return (env_init_base(path));
	return (env_array_realloc(envp, env_array_get_size(envp)));
}

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
		return (panic(glb, CODE_MALLOC, NULL), 1);
	pos = env_key_get_pos(glb->env, key);
	if (pos != KEY_NOT_FOUND)
		return (free(glb->env[pos]), glb->env[pos] = s, 1);
	size = env_array_get_size(glb->env) + 1;
	new = env_array_realloc(glb->env, size);
	if (!new)
		return (free(s), panic(glb, CODE_MALLOC, NULL), 1);
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
