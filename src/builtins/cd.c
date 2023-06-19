/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:48:36 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/19 15:27:03 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_glb *glb)
{
	char	*tmp;
	char	buf[PATH_MAX];

	tmp = env_getenv(glb->env, "PWD");
	if (!tmp)
		glb->env = env_key_add(glb->env, f_strjoin("OLDPWD=", ""));
	else
		glb->env = env_key_add(glb->env, f_strjoin("OLDPWD=", tmp));
	if (!glb->env)
		panic(glb, CODE_MALLOC, NULL);
	tmp = f_strjoin("PWD=", getcwd(buf, PATH_MAX));
	if (!tmp)
		return (perror("minishell: cd: getcwd"));
	glb->env = env_key_add(glb->env, tmp);
	if (!glb->env)
		panic(glb, CODE_MALLOC, NULL);
}

static int	blt_cd_update_rval(char *path, int argc, char **argv)
{
	if (argv[1] && !*argv[1])
		return (1);
	if (argc > 2)
	{
		g_rval = 1;
		f_dprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		return (1);
	}
	if (argc == 1 && (!path || !*path))
	{
		g_rval = 1;
		f_dprintf(STDERR_FILENO, "minishell: cd: HOME not set\n");
		return (1);
	}
	return (0);
}

void	blt_cd(t_glb *glb, int argc, char **argv)
{
	char	*path;

	g_rval = 0;
	path = env_getenv(glb->env, "HOME");
	if (blt_cd_update_rval(path, argc, argv))
		return ;
	if (argc == 1)
	{
		if (chdir(path))
		{
			g_rval = 1;
			f_dprintf(STDERR_FILENO, "minishell: cd: %s: ", path);
			perror("");
		}
	}
	else if (chdir(argv[1]))
	{
		g_rval = 1;
		f_dprintf(STDERR_FILENO, "minishell: cd: %s: ", argv[1]);
		perror("");
	}
	update_pwd(glb);
}
