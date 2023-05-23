/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:41:39 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/23 15:47:48 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**env_init_base(char **env, char *path)
{
	int		shlvl;
	char	*tmp;

	if (env && !env_getenv(env, "PWD"))
		env = env_key_add(env, f_strjoin("PWD=", path));
	if (env && !env_getenv(env, "SHLVL"))
		env = env_key_add(env, f_strdup("SHLVL=1"));
	else if (env)
	{
		shlvl = f_atoi(env_getenv(env, "SHLVL"));
		shlvl++;
		tmp = f_itoa(shlvl);
		if (tmp)
			env = env_key_add(env, f_strjoin("SHLVL=", tmp));
		free(tmp);
	}
	if (env && !env_getenv(env, "_"))
		env = env_key_add(env, f_strdup("_=/usr/bin/env"));
	return (env);
}

char	**env_init(char **envp)
{
	char	**new;
	char	path[PATH_MAX];

	if (!getcwd(path, PATH_MAX))
		return (perror("minishell: getcwd: "), NULL);
	new = env_array_realloc(envp, env_array_get_size(envp));
	if (!new)
		return (NULL);
	return (env_init_base(new, path));
}

char	*env_getenv(char **env, char *s)
{
	char	*p;
	int		pos;

	pos = env_key_get_pos(env, s);
	if (pos == KEY_NOT_FOUND)
		return (NULL);
	p = f_strchr(env[pos], '=');
	if (p)
		return (++p);
	return (env[pos] + f_strlen(env[pos]));
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
		return (free(env[pos]), env[pos] = key, env);
	size = env_array_get_size(env) + 1;
	new = env_array_realloc(env, size);
	if (!new)
		return (env_array_destroy(env, env_array_get_size(env)), free(key),
			NULL);
	env_array_destroy(env, env_array_get_size(env));
	new[size - 1] = key;
	return (new);
}

/**
 * @brief Remove a key from the environment. Key must be of the form 'key'.
 */
void	env_key_del(char **env, char *key)
{
	int	pos;

	pos = env_key_get_pos(env, key);
	if (pos == KEY_NOT_FOUND)
		return ;
	free(env[pos]);
	while (env[pos])
	{
		env[pos] = env[pos + 1];
		pos++;
	}
}
