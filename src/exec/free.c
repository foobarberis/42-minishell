#include "../inc/minishell.h"

void free_double_array(char **args);
void free_t_output(t_output *output);
void	free_t_input(t_input *input);

void	free_t_cmd(t_cmd *cmd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd) {
		if (cmd[i].args)
			free_double_array(cmd[i].args);
		if (cmd[i].path_cmd)
			free(cmd[i].path_cmd);
		if (cmd[i].input)
			free(cmd[i].input);
		if (cmd[i].limiter)
			free(cmd[i].limiter);
		if (cmd[i].string_here_doc)
			free(cmd[i].string_here_doc);
		if (cmd[i].output)
			free(cmd[i].output);
		i++;
	}
	free(cmd);
}

void free_double_array(char **args)
{
	int i;

	if (!args)
		return;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
