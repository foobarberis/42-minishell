#include "minishell.h"
#include "execution.h"

int	open_all_redirects(t_input *input, t_output *output)
{
	int	error;

	error = open_input(input);
	if (error == ERROR_REDIRECT)
		return (ERROR_REDIRECT);
	error = open_ouptut;
	if (error == ERROR_REDIRECT)
		return (ERROR_REDIRECT);
	reuturn (error);
}

int	open_input(t_input *files)
{
	int	i;
	int	valid;

	i = 0;
	while (files[i]->type)
	{
		valid = open(files[i]->input, O_RDONLY);
		if (valid != SUCCESS)
		{
			perror(files[i]->input);
			return (ERROR_REDIRECT);
		}
		i++;
	}
	return (i - 1);
}

int	open_output(t_output files)
{
	int	i;
	int	valid;

	i = 0;
	while (files[i]->file)
	{
		if (files[i]->type == S_OUTPUT_CHEVRON)
			valid = open(files[i]->output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			valid = open(files[i]->output, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (valid != SUCCESS)
		{
			perror(files[i]->input);
			return (ERROR_REDIRECT);
		}
		i++;
	}
	return (i - 1);
}
