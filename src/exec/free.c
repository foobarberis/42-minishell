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
		if (cmd[i].struct_input)
			free_t_input(cmd[i].struct_input);
		if (cmd[i].struct_output)
			free_t_output(cmd[i].struct_output);
		i++;
	}
	free(cmd);
}

void	free_t_input(t_input *input)
{
//	int i;
//
//	i = 0;
	if (!input)
		return;
//	while (i < input[i].fd_input) {
		if (input->input)
			free(input->input);
		if (input->limiter)
			free(input->limiter);
		if (input->string_here_doc)
			free(input->string_here_doc);
//		i++;
//	}
	free(input);
}

void free_t_output(t_output *output)
{
//	int i;
//
//	i = 0;
	if (!output)
		return;
//	while (i < output[i].fd_output)
//	{
		if (output->output)
			free(output->output);
//		i++;
//	}
	free(output);
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
