/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:45:37 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/01 11:09:34 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2) && (*s1 != '=' && *s2 != '=')
		&& (*s1 != '+' && *s2 != '+'))
	{
		s1++;
		s2++;
	}
	if ((*s1 == '+' || *s1 == '=' || !*s1)
		&& (*s2 == '+' || *s2 == '=' || !*s2))
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

size_t	env_array_get_size(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	env_array_destroy(char **env, size_t size)
{
	size_t	i;

	i = 0;
	if (!env)
		return ;
	while (env[i] && i < size)
		free(env[i++]);
	free(env);
}

char	**env_array_realloc(char **env, size_t size)
{
	size_t	i;
	char	**new;

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

int	env_key_get_pos(char **env, char *key)
{
	int	pos;

	pos = 0;
	while (env[pos])
	{
		if (!env_strcmp(key, env[pos]))
			return (pos);
		pos++;
	}
	return (KEY_NOT_FOUND);
}
