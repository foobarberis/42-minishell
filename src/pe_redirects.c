#include "minishell.h"
#include "../inc/execution.h"

char	*ft_strdup(const char *s1)
int		open_input(t_input *files);
int		open_output(t_output *files);

int	open_all_redirects(t_input *input, t_output *output, int *final_output, int *final_input)
{
	int valid;

	valid = open_input(input);
	if (valid == ERROR_REDIRECT)
		return (ERROR_REDIRECT);
	final_input = ft_strdup(files[valid]->input);
	valid = open_output(output);
	if (valid == ERROR_REDIRECT)
		return (ERROR_REDIRECT);
	final_output = ft_strdup(files[valid]->output);
	return (valid);
}
/** finir mon changement de redire */
int	open_input(t_input *files, char *final_input)
{
	int	i;
	int	valid;

	i = 0;
	valid = 0;
	while (files[i]->type)
	{
		if (files[i]->type == S_INPUT_CHEVRON)
			valid = open(files[i]->input, O_RDONLY);
		if (valid != SUCCESS)
		{
			perror(files[i]->input);
			return (ERROR_REDIRECT);
		}
		if (files[i]->type == S_INPUT_CHEVRON && files[i + 1]->input)
			close(valid)
		i++;
	}
	files->fd_input = valid;
	return (i - 1);
}

int	open_output(t_output *files)
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
			perror(files[i]->output);
			return (ERROR_REDIRECT);
		}
		if (files[i + 1]->output)
			close(valid)
		i++;
	}
	files->fd_output = valid;
	return (i - 1);
}

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len_s1;
	char	*dup;

	i = 0;
	len_s1 = ft_strlen((char *)s1);
	dup = malloc(sizeof(char) * len_s1 + 1);
	if (!dup)
		return (NULL);
	if (len_s1 == 0)
	{
		dup[i] = '\0';
		return (dup);
	}
	while (i < len_s1)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
