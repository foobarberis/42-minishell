#include "../../inc/minishell.h"

void	close_fd(t_cmd *cmd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		if (cmd[i].input)
			close(cmd[i].final_input);
		else if (cmd[i].fd[0])
			close(cmd[i].fd[0]);
		if (cmd[i].output)
			close (cmd[i].final_output);
		else if (cmd[i].fd[1])
			close(cmd[i].fd[1]);
		i++;
	}
}
