/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:05:28 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/12 10:54:50 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_cmd *cmd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		if (cmd[i].input)
			close(cmd[i].final_input);
		if (cmd[i].fd[0])
			close(cmd[i].fd[0]);
		if (cmd[i].output)
			close (cmd[i].final_output);
		if (cmd[i].fd[1])
			close(cmd[i].fd[1]);
		i++;
	}
}
