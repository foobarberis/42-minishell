#include "../inc/minishell.h"

int	free_t_cmd(t_cmd *cmd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		if (cmd[i].args)
			ft_free_double_array(cmd[i].args);
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
		init_to_null_cmd_struct(&cmd[i], nb_cmd);
		i++;
	}
	free(cmd);
	return (1);
}

char	**ft_free_double_array(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (NULL);
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
	return (NULL);
}
