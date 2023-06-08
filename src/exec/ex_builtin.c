/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:05:36 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/08 11:04:57 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_builtin(t_glb *glb, t_cmd *cmd, int builtin, char **arg)
{
	if (builtin == ECHO)
		blt_echo(arg);
	else if (builtin == CD)
		blt_cd(glb, blt_compute_argc(arg), arg);
	else if (builtin == PWD)
		blt_pwd();
	else if (builtin == EXPORT)
		blt_export(glb, blt_compute_argc(arg), arg);
	else if (builtin == UNSET)
		blt_unset(glb, arg);
	else if (builtin == ENV)
		blt_env(glb);
	else if (builtin == EXIT)
		blt_exit(glb, cmd, (int)blt_compute_argc(arg), arg);
}

void close_unused(t_cmd *cmd)
{
	if (cmd->final_input >= REDIRECTION && cmd->final_output > REDIRECTION)
	{
		close (cmd->final_input);
		close(cmd->final_output);
	}
	if (cmd->final_output > REDIRECTION)
	{
		close(cmd->final_output);
	}
	if (cmd->final_input > REDIRECTION)
	{
		close(cmd->final_input);
	}
	close(cmd->fd[0]);
	close(cmd->fd[1]);
}