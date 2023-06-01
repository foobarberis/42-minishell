/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:41:39 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/01 09:21:51 by mbarberi         ###   ########.fr       */
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
		return (perror("minishell: getcwd"), NULL);
	new = env_array_realloc(envp, env_array_get_size(envp));
	if (!new)
		return (NULL);
	return (env_init_base(new, path));
}

/**
 * @brief The getenv() function searches the environment list to find the
 * environment variable name, and returns a pointer to the corresponding
 * value string.
 * @param env The environment.
 * @param name The string to find.
 * @return A pointer to the value associated with name. If the name was not
 * found, returns NULL. If the name was found has no value associated to
 * it, retuns a pointer to the termninating NULL character.
 */
char	*env_getenv(char **env, char *name)
{
	char	*p;
	int		pos;

	pos = env_key_get_pos(env, name);
	if (pos == KEY_NOT_FOUND)
		return (NULL);
	p = f_strchr(env[pos], '=');
	if (p)
		return (++p);
	return (env[pos] + f_strlen(env[pos]));
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
