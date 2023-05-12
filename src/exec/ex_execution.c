#include "../inc/minishell.h"

void	child_exec(t_cmd *cmd, size_t i, size_t nb_cmd);
void	parent_exec(t_cmd *cmd, size_t i);

int	ex_execution(t_cmd *cmd, size_t nb_cmd)
{
	size_t	i;
	int	pid;

	i = 0;
//	if (nb_cmd == 1 && cmd[i]->is_builtin)
//	{
//		ex_builtin(cmd[i]->is_builtin, cmd[i]->args);
//		i++;
//	}
	while (i < nb_cmd)
	{
		while (cmd[i].error_redirect == 1)
		{
			dprintf(2,"je passe ici et lq\n");
			i++;
			if (i == nb_cmd)
				break ;
		}
		pid = fork();
		cmd[i].pid = pid;
		if (pid == -1)
			perror(" :fork failed\n");
		if (pid == 0)
			child_exec(cmd, i, nb_cmd);
		parent_exec(cmd, i);
		i++;
	}
	close(cmd[i - 1].fd[0]);
	return (SUCCESS);
}

void	parent_exec(t_cmd *cmd, size_t i)
{
	if (cmd[i].final_input >= REDIRECTION && cmd[i].final_output > REDIRECTION)
	{
		if (cmd[i].is_here_doc == 0)
			close (cmd[i].final_input);
		close(cmd[i].final_output);
	}
	else if (cmd[i].final_input >= REDIRECTION)
	{
		if (cmd[i].is_here_doc == 0)
			close(cmd[i].final_input);
	}
	else if (cmd[i].final_output > REDIRECTION)
		close(cmd[i].final_output);
	close(cmd[i].fd[1]);
	if (i > 0)
		close(cmd[i - 1].fd[0]);
}

void	child_exec(t_cmd *cmd, size_t i, size_t nb_cmd)
{
	if (cmd[i].final_input < REDIRECTION && cmd[i].final_output < REDIRECTION)
		nothing_to_redirect(cmd, i, nb_cmd);
	else if (cmd[i].final_input >= REDIRECTION && \
											cmd[i].final_output > REDIRECTION)
		in_out_redirect(cmd, i);
	else if (cmd[i].final_input >= REDIRECTION)
		in_redirect(cmd, i, nb_cmd);
	else if (cmd[i].final_output > REDIRECTION)
		out_redirect(cmd, i);
	if (i > 0)
		close(cmd[i - 1].fd[0]);
	close(cmd[i].fd[0]);
	close (cmd[i].fd[1]);
//	if (cmd[i].is_builtin)
//		ex_builtin(cmd[i].is_builtin, cmd[i].args);
//	else
		execve(cmd[i].path_cmd, cmd[i].args, cmd[i].env);
	exit(1);
}
