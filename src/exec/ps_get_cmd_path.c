#include "minishell.h"

void	errors(char *cmd);
char	*ft_grep_path(char **envp);
char	*ft_compute_path(char **path, char *cmd);

/* FIXME: Can this be replaced with env_getenv ? */
int	ps_get_path_cmd(char *cmd, char **envp, char **path_cmd)
{
	char	*path;
	char	**split_path;

	if (cmd == NULL)
	{
		printf(": command not found:\n");
		return (ERROR);
	}
	path = ft_grep_path(envp);
	split_path = ft_split(path, ':');
	if (split_path == NULL || path == NULL)
	{
		printf(" : no such file or directory: %s\n", cmd);
		return (ERROR);
	}
	*path_cmd = ft_compute_path(split_path, cmd);
	ft_free_split(split_path);
	if (*path_cmd == NULL)
		return (errors(cmd), ERROR);
	return (SUCCESS);
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
		if (buff == NULL)
			return (NULL);
		path_test = f_strjoin(buff, cmd);
		free(buff);
		if (path_test == NULL)
			return (NULL);
		if (access(path_test, X_OK) == 0)
			return (path_test);
		free(path_test);
		i++;
	}
	return (NULL);
}

void	errors(char *cmd)
{
	printf("Minishell : command not found: %s\n", cmd);
}