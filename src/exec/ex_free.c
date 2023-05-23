#include "../inc/minishell.h"

int	free_t_cmd(t_cmd *cmd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		if (cmd[i].args)
			ft_free_double_array(cmd[i].args); /* FIXME: This causes `attempting free on address which was not malloc()-ed' when using panic() inside exit.*/
		if (cmd[i].path_cmd)
			free(cmd[i].path_cmd);
		if (cmd[i].input)
			free(cmd[i].input);
		if (cmd[i].output)
			free(cmd[i].output);
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
