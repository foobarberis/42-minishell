/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:42:19 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/11 10:43:34 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_list_get_size(t_env **env)
{
	size_t	i;
	t_env	*curr;

	i = 0;
	curr = *env;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

char	*env_join_key_value(t_env *node)
{
	char	*p;
	char	*q;

	p = f_strjoin(node->key, "=");
	if (!p)
		return (NULL);
	q = f_strjoin(p, node->value);
	return (free(p), q);
}

void	env_envp_update(t_glb *glb)
{
	char	**new;
	t_env	*curr;
	size_t	i;

	i = env_list_get_size(glb->env);
	new = malloc((i + 1) * sizeof(char *));
	if (!new)
		panic(glb, CODE_MALLOC);
	new[i] = NULL;
	i = 0;
	curr = glb->env[0];
	while (curr)
	{
		new[i] = env_join_key_value(curr);
		if (!new[i++])
			return (env_environ_free(new), panic(glb, CODE_MALLOC));
		curr = curr->next;
	}
	if (glb->environ)
		env_environ_free(glb->environ);
	glb->environ = new;
}
