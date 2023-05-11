#include "minishell.h"

char	*f_strdup(const char *s1);

int	open_input(t_cmd *files)
{
	int	valid;

	valid = -1;
	if (files->type_in == S_INPUT)
		valid = open(files->input, O_RDONLY);
	else
	{
		here_doc(files->limiter, &files->string_here_doc);
		files->is_here_doc = 1;
		valid = 0;
	}
	if (valid < SUCCESS)
	{
		perror(files->input);
		return (ERROR_REDIRECT);
	}
	if (valid == -1)
		return (NO_REDIRECTION);
	return (valid);
}

int	open_output(t_cmd *files)
{
	int	valid;

	valid = -1;
	if (files->type_out == S_OUTPUT)
		valid = open(files->output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		valid = open(files->output, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (valid < SUCCESS)
		return (perror(files->output), ERROR_REDIRECT);
	if (valid == -1)
		return (NO_REDIRECTION);
	return (valid);
}
