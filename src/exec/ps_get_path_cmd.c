/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_get_path_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:10:13 by vburton           #+#    #+#             */
/*   Updated: 2023/06/20 09:31:27 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_compute_path(char **path, char *cmd)
{
	int		i;
	char	*buff;
	char	*path_test;

	i = 0;
	if (access(cmd, X_OK) == 0 && f_strchr(cmd, '/'))
		return (f_strdup(cmd));
	while (path && path[i])
	{
		buff = f_strjoin(path[i], "/");
		if (!buff)
			return (ERR_MALLOC);
		if (buff == NULL)
			return (NULL);
		path_test = f_strjoin(buff, cmd);
		free(buff);
		if (!path_test)
			return (ERR_MALLOC);
		if (access(path_test, X_OK) == 0)
			return (path_test);
		free(path_test);
		i++;
	}
	return (NULL);
}

int	check_cmd(char *cmd)
{
	DIR	*dir;
	int	error;

	error = 0;
	dir = opendir(cmd);
	if (!f_strcmp(cmd, "."))
	{
		f_dprintf(2, "minishell: .: filename argument required\n");
		error = ERROR;
	}
	else if (access(cmd, X_OK) && f_strchr(cmd, '/'))
	{
		perror(cmd);
		error = ERROR;
	}
	else if (dir && f_strchr(cmd, '/'))
	{
		f_dprintf(2, "minishell: %s: Is a directory\n", cmd);
		error = ERROR;
	}
	closedir(dir);
	return (error);
}

char	*ps_get_path_cmd(char *cmd, char **envp, char *path_cmd)
{
	char	*path;
	char	**split_path;

	if (cmd == NULL || !*cmd)
	{
		if (cmd && !*cmd)
			f_dprintf(2, ": command not found\n");
		return (NULL);
	}
	if (check_cmd(cmd) == ERROR)
		return (NULL);
	path = env_getenv(envp, "PATH");
	split_path = ft_split(path, ':');
	if ((split_path == NULL || path == NULL) && access(cmd, X_OK))
	{
		f_dprintf(2, "minishell: %s: no such file or directory\n", cmd);
		return (NULL);
	}
	path_cmd = ft_compute_path(split_path, cmd);
	ft_free_double_array(split_path);
	if (path_cmd && f_strcmp(path_cmd, ERR_MALLOC) == 0)
		return (ERR_MALLOC);
	if (path_cmd == NULL)
		return (f_dprintf(2, "minishell : %s: command not found\n", cmd), NULL);
	return (path_cmd);
}
