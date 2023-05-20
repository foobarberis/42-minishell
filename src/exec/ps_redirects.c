#include "minishell.h"

int	open_input(t_cmd *files)
{
	int	valid;

	valid = -1;
	if (files->type_in == S_INPUT)
		valid = open(files->input, O_RDONLY);
	else
	{
		files->string_here_doc = here_doc(files->limiter);
		// FIXME: Add check for NULL
		files->is_here_doc = 1;
		valid = 0;
	}
	if (valid < SUCCESS)
	{
		files->is_valid = ERROR;
		perror(files->input);
		return (ERROR_REDIRECT);
	}
	return (valid);
}

/* int	open_input(t_cmd *cmd)
{
	int fd;

	fd = -1;
	if (cmd->type_in == S_INPUT)
		return (open(cmd->input, O_RDONLY));
	else
	{
		cmd->string_here_doc = here_doc(cmd->limiter);
		if (!cmd->string_here_doc)
			return (ERROR_REDIRECT);
		cmd->is_here_doc = 1;
		valid = 0;
	}
	if (valid < SUCCESS)
	{
		cmd->is_valid = ERROR;
		perror(cmd->input);
		return (ERROR_REDIRECT);
	}
	return (valid);
} */

int	open_output(t_cmd *files)
{
	int	valid;

	valid = -1;
	if (files->type_out == S_OUTPUT)
		valid = open(files->output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		valid = open(files->output, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (valid < SUCCESS)
	{
		files->is_valid = ERROR;
		perror(files->output);
		return (ERROR_REDIRECT);
	}
	return (valid);
}
