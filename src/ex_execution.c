#include "../inc/execution.h"

void	nothing_to_redirect(t_cmd *cmd, int i, int nb_cmd);
void	in_out_redirect(t_cmd *cmd, int i);
void	in_redirect(t_cmd *cmd, int i, int nb_cmd);
void	out_redirect(t_cmd *cmd, int i);
void	child_exec(t_cmd *cmd, int i, int nb_cmd);
void	parent_exec(t_cmd *cmd, int i);

int	ex_execution(t_cmd *cmd, int nb_cmd)
{
	int	i;
	int	pid;

	i = 0;
	while (i < nb_cmd)
	{
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

void	parent_exec(t_cmd *cmd, int i)
{
	if (cmd[i].final_input > REDIRECTION && cmd[i].final_output > REDIRECTION)
	{
		close (cmd[i].final_input);
		close(cmd[i].final_output);
	}
	else if (cmd[i].final_input > REDIRECTION)
		close(cmd[i].final_input);
	else if (cmd[i].final_output > REDIRECTION)
		close(cmd[i].final_output);
	close(cmd[i].fd[1]);
	if (i > 0)
		close(cmd[i - 1].fd[0]);
}

void	child_exec(t_cmd *cmd, int i, int nb_cmd)
{
	if (cmd[i].final_input < REDIRECTION && cmd[i].final_output < REDIRECTION)
		nothing_to_redirect(cmd, i, nb_cmd);
	else if (cmd[i].final_input > REDIRECTION && \
											cmd[i].final_output > REDIRECTION)
		in_out_redirect(cmd, i);
	else if (cmd[i].final_input > REDIRECTION)
		in_redirect(cmd, i, nb_cmd);
	else if (cmd[i].final_output > REDIRECTION)
		out_redirect(cmd, i);
	if (i > 0)
		close(cmd[i - 1].fd[0]);
	close(cmd[i].fd[0]);
	close (cmd[i].fd[1]);
	execve(cmd[i].path_cmd, cmd[i].args, cmd[i].env->envp);
	exit(1);
}

void	nothing_to_redirect(t_cmd *cmd, int i, int nb_cmd)
{
	if (i > 0)
		dup2(cmd[i - 1].fd[0], STDIN_FILENO);
	if (i < nb_cmd - 1)
		dup2(cmd[i].fd[1], STDOUT_FILENO);
}

void	in_out_redirect(t_cmd *cmd, int i)
{
	dup2(cmd[i].final_input, STDIN_FILENO);
	close (cmd[i].final_input);
	dup2(cmd[i].final_output, STDOUT_FILENO);
	close(cmd[i].final_output);
}

void	in_redirect(t_cmd *cmd, int i, int nb_cmd)
{
	dup2(cmd[i].final_input, STDIN_FILENO);
	close (cmd[i].final_input);
	if (i < nb_cmd - 1)
		dup2(cmd[i].fd[1], STDOUT_FILENO);
}

void	out_redirect(t_cmd *cmd, int i)
{
	if (i > 0)
		dup2(cmd[i - 1].fd[0], STDIN_FILENO);
	dup2(cmd[i].final_output, STDOUT_FILENO);
	close (cmd[i].final_output);
}
