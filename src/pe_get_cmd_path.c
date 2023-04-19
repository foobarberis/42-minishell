#include "minishell.h"
#include "execution.h"


char	*ft_grep_path(char **envp);
char	*ft_compute_path(char **path, char *cmd);

char	*ft_path_cmd(char *cmd, char **envp)
{
    char    *path;
    char    **split_path;
    char    *path_cmd;

	if (cmd == NULL)
    {
        ft_printf(": command not found:\n");
		return (NULL);
    }
	path = ft_grep_path(envp);
    split_path = ft_split(path, ':');
	if (split_path == NULL || path == NULL)
	{
		ft_printf(" : no such file or directory: %s\n", cmd);
		return (NULL);
	}
	path_cmd = ft_compute_path(split_path, cmd[0]);
	ft_free_split(split_path);
	if (path_cmd == NULL)
		ft_printf(" : no such file or directory: %s\n", cmd);
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
		ft_strdup(cmd);
		return (cmd);
	}
	while (path[i])
	{
		buff = ft_strjoin(path[i], "/");
		if (buff == NULL)
			return (NULL);
		path_test = ft_strjoin(buff, cmd);
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