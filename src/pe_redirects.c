#include "minishell.h"
#include "../inc/execution.h"

char	*open_input(t_input *files);
char	*open_output(t_output *files);

int	open_all_redirects(t_input *input, t_output *output, char *final_output, char *final_input)
{
	final_output = open_input(input);
	if (valid == ERROR_REDIRECT)
		return (ERROR_REDIRECT);
	valid = open_ouptut;
	if (valid == ERROR_REDIRECT)
		return (ERROR_REDIRECT);
	return (valid);
}
/** finir mon changement de redire */
char	*open_input(t_input *files)
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

char	*open_output(t_output *files)
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
