/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:37:47 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/24 12:38:28 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_max_cmd(t_token **tok)
{
	size_t	i;

	i = 0;
	if (!tok || !*tok)
		return (0);
	while (tok[i])
		i++;
	return (tok[i - 1]->cmd_index + 1);
}

static t_token	***init_array(t_token **tok)
{
	size_t	i;
	size_t	j;
	size_t	count;
	t_token	***new;

	i = 0;
	j = 0;
	new = f_calloc(get_max_cmd(tok) + 1, sizeof(t_token **));
	if (!new)
		return (NULL);
	while (tok[i])
	{
		count = 0;
		while (tok[i] && tok[i]->cmd_index == j)
		{
			count++;
			i++;
		}
		new[j] = f_calloc(count + 1, sizeof(t_token *));
		if (!new[j])
			return (token_split_destroy(new), NULL);
		j++;
	}
	return (new);
}

void	token_split_destroy(t_token ***split)
{
	size_t	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

t_token	***token_split_create(t_token **tok)
{
	int		i;
	int		j;
	t_token	***new;

	i = 0;
	j = 0;
	new = init_array(tok);
	if (!new)
		return (NULL);
	while (tok[j])
	{
		new[tok[j]->cmd_index][i] = tok[j];
		if (tok[j + 1] && (tok[j]->cmd_index != tok[j + 1]->cmd_index))
			i = 0;
		else
			i++;
		j++;
	}
	return (new);
}
