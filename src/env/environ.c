/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:42:19 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/12 10:41:04 by mbarberi         ###   ########.fr       */
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
	char	*tmp;
	char	*new;

	new = f_strjoin(node->key, "=");
	if (!new)
		return (NULL);
	if (node->value)
		return (tmp = f_strjoin(new, node->value), free(new), tmp);
	return (new);
}

static char	**env_environ_list_to_array(t_env **env)
{
	size_t	i;
	char	**new;
	t_env	*curr;

	i = env_list_get_size(env);
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	new[i] = NULL;
	i = 0;
	curr = *env;
	while (curr)
	{
		new[i] = env_join_key_value(curr);
		if (!new[i++])
			return (env_environ_free(new), NULL);
		curr = curr->next;
	}
	return (new);
}

void	env_environ_update(t_glb *glb)
{
	if (glb->environ)
		env_environ_free(glb->environ);
	glb->environ = env_environ_list_to_array(glb->env);
	if (!glb->environ)
		panic(glb, CODE_MALLOC,NULL);
}
