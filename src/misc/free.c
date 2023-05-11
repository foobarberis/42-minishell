/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:37:44 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/11 10:43:15 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* WARNING: The called must free tok. */
void	ps_token_list_free(t_token **tok)
{
	t_token	*curr;
	t_token	*next;

	curr = *tok;
	while (curr)
	{
		next = curr->next;
		ps_token_list_node_destroy(curr);
		curr = next;
	}
}

/* WARNING: The called must free env. */
void	env_list_free(t_env **env)
{
	t_env	*curr;
	t_env	*next;

	curr = *env;
	while (curr)
	{
		next = curr->next;
		env_list_node_destroy(curr);
		curr = next;
	}
}

/* This function free's envp. */
void	env_environ_free(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}
