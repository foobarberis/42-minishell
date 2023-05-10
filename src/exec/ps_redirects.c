#include "minishell.h"

char	*f_strdup(const char *s1);
int		open_input(t_input *files);
int		open_output(t_output *files);

int	ps_open_redirect(t_input *in, t_output *out, int *final_out, int *final_in)
{
	int	valid;

	valid = open_input(in);
	if (valid == ERROR_REDIRECT)
		return (ERROR_REDIRECT);
	*final_in = valid;
	valid = open_output(out);
	if (valid == ERROR_REDIRECT)
		return (ERROR_REDIRECT);
	*final_out = valid;
	return (valid);
}

int	open_input(t_input *files)
{
	int	i;
	int	count;
	int	valid;

	i = 0;
	count = 0;
	if (files)
		count = files[i].fd_input;
	valid = -1;
	while (i < count)
	{
		if (files[i].type == S_INPUT)
			valid = open(files[i].input, O_RDONLY);
		else
		{
			files[i].string_here_doc = here_doc(files[i].limiter);
			files[i].is_here_doc = 1;
			valid = 0;
		}
		if (valid < SUCCESS)
		{
			perror(files[i].input);
			return (ERROR_REDIRECT);
		}
		if (i + 1 < count && files->is_here_doc == 0)
			close(valid);
		i++;
	}
	if (valid == -1)
		return (NO_REDIRECTION);
	return (valid);
}

int	open_output(t_output *files)
{
	int	i;
	int	count;
	int	valid;

	i = 0;
	count = 0;
	if (files)
		count = files[i].fd_output;
	valid = -1;
	while (i < count)
	{
		if (files[i].type == S_OUTPUT)
			valid = open(files[i].output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			valid = open(files[i].output, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (valid < SUCCESS)
			return (perror(files[i].output), ERROR_REDIRECT);
		if (i + 1 < count)
			close(valid);
		i++;
	}
	if (valid == -1)
		return (NO_REDIRECTION);
	return (valid);
}
