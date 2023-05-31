/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:06:00 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/31 13:29:51 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	nothing_to_redirect(t_cmd *cmd, size_t i, size_t nb_cmd)
{
	if (i > 0 && cmd[i].is_builtin == 0)
		dup2(cmd[i - 1].fd[0], STDIN_FILENO);
	if (i < nb_cmd - 1)
		dup2(cmd[i].fd[1], STDOUT_FILENO);
}

void	in_out_redirect(t_cmd *cmd, size_t i)
{
	if (cmd[i].is_here_doc)
	{
		f_dprintf(cmd[i].fd[1], cmd[i].string_here_doc);
		dup2(cmd[i].fd[0], STDIN_FILENO);
	}
	else
	{
		dup2(cmd[i].final_input, STDIN_FILENO);
		close (cmd[i].final_input);
	}
	dup2(cmd[i].final_output, STDOUT_FILENO);
	close(cmd[i].final_output);
}

void	in_redirect(t_cmd *cmd, size_t i, size_t nb_cmd)
{
	if (cmd[i].is_here_doc)
	{
		f_dprintf(cmd[i].fd[1], cmd[i].string_here_doc);
		close(cmd[i].fd[1]);
		dup2(cmd[i].fd[0], STDIN_FILENO);
	}
	else
	{
		dup2(cmd[i].final_input, STDIN_FILENO);
		close (cmd[i].final_input);
	}
	if (i < nb_cmd - 1)
		dup2(cmd[i].fd[1], STDOUT_FILENO);
}

void	out_redirect(t_cmd *cmd, size_t i)
{
	if (i > 0)
		dup2(cmd[i - 1].fd[0], STDIN_FILENO);
	dup2(cmd[i].final_output, STDOUT_FILENO);
	close (cmd[i].final_output);
}
