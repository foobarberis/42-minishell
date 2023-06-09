/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:06:00 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/09 20:46:17 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	nothing_to_redirect(t_cmd *cmd, size_t i, size_t nb_cmd)
{
	int	check;

	check = 0;
	if (i > 0 && cmd[i].is_builtin == 0)
	{
		if (!f_strcmp(cmd[0].args[0], "cat") && cmd[0].args[1] == NULL)
			check = 1;
		if (check == 0 || (check == 1 && cmd[0].final_input))
			dup2(cmd[i - 1].fd[0], STDIN_FILENO);
	}
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
	int	pid;
	int	fd[2];

	if (cmd[i].is_here_doc)
	{
//		pipe(fd);
//		pid = fork();
//		if (pid == 0)
//		{
//			write(fd[0], cmd[i].string_here_doc, f_strlen(cmd[i].string_here_doc));
//			exit(0);
//		}
//		dup2(fd[1], STDIN_FILENO);
//		close(fd[1]);
//		close(fd[0]);
	}
	else
	{
		dup2(cmd[i].final_input, STDIN_FILENO);
		close (cmd[i].final_input);
	}
	if (i < nb_cmd - 1)
	{
		dup2(cmd[i].fd[1], STDOUT_FILENO);
		close (cmd[i].fd[1]);
	}
}

void	out_redirect(t_cmd *cmd, size_t i)
{
	if (i > 0)
		dup2(cmd[i - 1].fd[0], STDIN_FILENO);
	dup2(cmd[i].final_output, STDOUT_FILENO);
	close (cmd[i].final_output);
}
