#include "../inc/minishell.h"

void	free_double_array(char **args);

int	free_t_cmd(t_cmd *cmd, int nb_cmd)
{
	int i;

	i = 0;
	while (i < nb_cmd)
	{
		close_fd(cmd, nb_cmd);
		if (cmd[i].args)
			free_double_array(cmd[i].args);
		cmd[i].args = NULL;
		if (cmd[i].path_cmd)
			free(cmd[i].path_cmd);
		cmd[i].path_cmd = NULL;
		if (cmd[i].input)
			free(cmd[i].input);
		cmd[i].input = NULL;
		if (cmd[i].limiter)
			free(cmd[i].limiter);
		cmd[i].limiter = NULL;
		if (cmd[i].string_here_doc)
			free(cmd[i].string_here_doc);
		cmd[i].string_here_doc = NULL;
		if (cmd[i].output)
			free(cmd[i].output);
		cmd[i].output = NULL;
		i++;
	}
	free(cmd);
	return (1);
}

void	free_double_array(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void close_fd(t_cmd *cmd, int nb_cmd)
{
	int i;

	i = 0;
	while (i < nb_cmd)
	{
		if (cmd[i].fd[0])
			close(cmd[i].fd[0]);
		if (cmd[i].fd[1])
			close(cmd[i].fd[1]);
		if (cmd[i].input)
			close(cmd[i].final_input);
		if (cmd[i].output)
			close (cmd[i].final_output);
		i++;
	}
}
