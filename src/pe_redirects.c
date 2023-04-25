#include "minishell.h"
#include "../inc/execution.h"

char	*ft_strdup(const char *s1);
int		open_input(t_input *files);
int		open_output(t_output *files);

int	open_all_redirects(t_input *input, t_output *output, int *final_output, int *final_input)
{
	int valid;

	valid = open_input(input);
	if (valid == ERROR_REDIRECT)
		return (ERROR_REDIRECT);
	*final_input = valid;
	valid = open_output(output);
	if (valid == ERROR_REDIRECT)
		return (ERROR_REDIRECT);
	*final_output = valid;
	return (valid);
}

int	open_input(t_input *files)
{
	int	i;
	int count;
	int	valid;

	i = 0;
	count = 0;
	if (files)
		count = files[i].fd_input;
	valid = -1;
	while (i < count)
	{
		printf("i = %d et nb_input = %d\n", i, files[i].fd_input);
		if (files[i].type == R_INPUT)
			valid = open(files[i].input, O_RDONLY);
		if (valid < SUCCESS)
		{
			perror(files[i].input);
			return (ERROR_REDIRECT);
		}
		if (i + 1 < count)
			close(valid);
		i++;
	}
	if (valid == 0)
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
	while (i < count)
	{
		if (files[i].type == R_OUTPUT)
			valid = open(files[i].output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			valid = open(files[i].output, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (valid < SUCCESS)
		{
			perror(files[i].output);
			return (ERROR_REDIRECT);
		}
		if (i + 1 < count)
			close(valid);
		i++;
	}
	if (valid == 0)
		return (NO_REDIRECTION);
	return (valid);
}
