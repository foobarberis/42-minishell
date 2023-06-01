/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:06:00 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/01 15:10:26 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	nothing_to_redirect(t_cmd *cmd, size_t i, size_t nb_cmd)
{
	if (i > 0 && cmd[i].is_builtin == 0)
	{
//		if (f_strcmp(cmd[i].args[0], "cat") == 0 && f_strcmp(cmd[i - 1].args[0], "cat") == 0 && cmd[i - 1].args[1] == NULL && cmd[i - 1].final_input < 0 && cmd[i - 1].final_output < 0)
//		{
//			dprintf(2, " 1111111111111111111111111111111111je passe la11111111111111111111111111111111111\n");
//		}
		dprintf(2,"Type in = %d et type out = %d et i = %ld\n", cmd[i].type_in, cmd[i].type_out, i);
		if (f_strcmp(cmd[i].args[0], "cat") == 0 && f_strcmp(cmd[i - 1].args[0], "cat") == 0 && cmd[i - 1].args[1] == NULL && cmd[i].type_in == -1)
		{
			dprintf(2, " 1111111111111111111111111111111111je passe la11111111111111111111111111111111111\n");
		}
		else
		{
//			dprintf(2, "test 2, pid = %d, cmd = %s\n", cmd[i].pid, cmd[i].path_cmd);
			dup2(cmd[i - 1].fd[0], STDIN_FILENO);
		}
	}
	if (i < nb_cmd - 1)
	{
//		dprintf(2, "test 3, pid = %d, cmd = %s\n", cmd[i].pid, cmd[i].path_cmd);
		dup2(cmd[i].fd[1], STDOUT_FILENO);
	}
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
