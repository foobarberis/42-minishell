/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:05:36 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/30 14:08:49 by vburton          ###   ########.fr       */
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
		blt_unset(glb, blt_compute_argc(arg), arg);
	else if (builtin == ENV)
		blt_env(glb);
	else if (builtin == EXIT)
		blt_exit(glb, cmd, (int)blt_compute_argc(arg), arg);
}
