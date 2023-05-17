#include "minishell.h"

int		check_slash(char *cmd);
int		check_cmd(char *cmd);
char	*ft_grep_path(char **envp);
char	*ft_compute_path(char **path, char *cmd);

/* FIXME: Can this be replaced with env_getenv ? */
char	*ps_get_path_cmd(char *cmd, char **envp, char *path_cmd)
{
	char	*path;
	char	**split_path;

	if (cmd == NULL)
	{
		printf(": command not found:\n");
		return (NULL);
	}
	if (check_cmd(cmd) == ERROR)
		return (NULL);
	path = ft_grep_path(envp);
	split_path = ft_split(path, ':');
	if (split_path == NULL || path == NULL)
	{
		printf(" : no such file or directory: %s\n", cmd);
		return (NULL);
	}
	path_cmd = ft_compute_path(split_path, cmd);
	ft_free_split(split_path);
	if (path_cmd && f_strcmp(path_cmd, ERR_MALLOC) == 0)
		return (ERR_MALLOC);
	if (path_cmd == NULL)
		return (printf("Minishell : %s: command not found\n", cmd), NULL);
	return (path_cmd);
}

char	*ft_grep_path(char **envp)
{
	while (*envp && ft_strncmp("PATH", *envp, 4))
		(envp)++;
	if (*envp == NULL)
		return (NULL);
	return (*envp + 5);
}

char	*ft_compute_path(char **path, char *cmd)
{
	int		i;
	char	*buff;
	char	*path_test;

	i = 0;
	if (access(cmd, X_OK) == 0)
	{
		f_strdup(cmd);
		return (cmd);
	}
	while (path[i])
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

int	check_slash(char *cmd)
{
	int	i;
	int	slash;

	i = 0;
	slash = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			slash++;
		i++;
	}
	return (slash);
}

int	check_cmd(char *cmd)
{
	int	directory;
	int	error;

	directory = check_slash(cmd);
	error = 0;
	if (!f_strcmp(cmd, "."))
	{
		dprintf(2, "Minishell: .: filename argument required\n");
		error = ERROR;
	}
	else if (access(cmd, X_OK) && directory > 0)
	{
		perror(cmd);
		error = ERROR;
	}
	else if (opendir(cmd))
	{
		dprintf(2, "Minishell: %s: Is a directory\n", cmd);
		error = ERROR;
	}
	return (error);
}
