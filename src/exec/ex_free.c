/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:05:54 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/09 18:27:25 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	free_t_cmd(t_cmd *cmd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		if (cmd[i].args)
			ft_free_double_array(cmd[i].args);
		if (cmd[i].path_cmd)
			free(cmd[i].path_cmd);
		if (cmd[i].input)
			free(cmd[i].input);
		if (cmd[i].output)
			free(cmd[i].output);
		i++;
	}
	free(cmd);
	return (1);
}

char	**ft_free_double_array(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (NULL);
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
	return (NULL);
}
