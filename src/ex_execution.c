#include "../inc/execution.h"
#include "../inc/minishell.h"

void print_fd(int fd);

/* Penser avant la boucle readline a save stdin et stdout dans 2 variables
les dup2 pour leur redonner leur indice de depart a la fin d'une cmd si il y a eu une redirection*/
//int	main_execution(t_glob data)
//{
//	if (data.multiple_cmd == NONE)
//		single_exection(data.cmd);
//
//}

int	single_execution(t_cmd cmd)
{
	int pid;
//	if (cmd.builtin != NONE)
//	{
//		if (cmd.final_input == NO_REDIRECTION)
//			close(cmd.fd[0]);
//		else
//			close(cmd.final_input);
//		if (cmd.final_output == NO_REDIRECTION)
//			close(cmd.fd[1]);
//		else
//		{
//			dup2(cmd.final_output, STDOUT_FILENO);
//			close (cmd.final_output);
//		}
//		exec_builtin(cmd.builtin, cmd.args);
//	}
//	else
//	{
	pid = fork();
	cmd.pid = pid;
	if (pid == -1)
	 	   {
			   perror(" :fork failed\n");
		   }
	if (pid == 0)
	    {
			if (cmd.final_input < REDIRECTION && cmd.final_output < REDIRECTION)
			{
				close(cmd.fd[0]);
				close(cmd.fd[1]);
			}
			else if (cmd.final_input > REDIRECTION && cmd.final_output > REDIRECTION)
			{
				close(cmd.fd[0]);
				close(cmd.fd[1]);
				dup2(cmd.final_input, STDIN_FILENO);
				close(cmd.final_input);
				dup2(cmd.final_output, STDOUT_FILENO);
				close(cmd.final_output);
			}
			else if (cmd.final_input > REDIRECTION)
			{
				close(cmd.fd[0]);
				close(cmd.fd[1]);
				dup2(cmd.final_input, STDIN_FILENO);
				close(cmd.final_input);
			}
			else if (cmd.final_output > REDIRECTION)
			{
				close(cmd.fd[0]);
				close(cmd.fd[1]);
				dup2(cmd.final_output, STDOUT_FILENO);
				close(cmd.final_output);
			}
			execve(cmd.path_cmd, cmd.args, cmd.env->envp);
			//			ft_free(cmd.args, nb_cmd);
			exit(1);
		}
	if (cmd.final_input < REDIRECTION && cmd.final_output < REDIRECTION)
	{
		close(cmd.fd[1]);
//		dup2(cmd.fd[0], STDIN_FILENO);
		close(cmd.fd[0]);
	}
	else if (cmd.final_input > REDIRECTION && cmd.final_output > REDIRECTION)
	{
		close(cmd.fd[0]);
		close(cmd.fd[1]);
		close(cmd.final_input);
		close(cmd.final_output);
	}
	else if (cmd.final_input > REDIRECTION)
	{
		close(cmd.fd[0]);
		close(cmd.fd[1]);
		close(cmd.final_input);
	}
	else if (cmd.final_output > REDIRECTION)
	{
		close(cmd.fd[0]);
		close(cmd.fd[1]);
		close(cmd.final_output);
	}
		return (SUCCESS);
}

int	multiple_execution(t_cmd *cmd, int nb_cmd)
{
	int i;
	int pid;

	i = 0;
	while (i < nb_cmd)
	{
		pid = fork();
		cmd[i].pid = pid;
		if (pid == -1) {
			perror(" :fork failed\n");
		}
		if (pid == 0) {
			if (cmd[i].final_input < REDIRECTION && cmd[i].final_output < REDIRECTION)
			{
				if (i > 0) {
					dup2(cmd[i - 1].fd[0], STDIN_FILENO);
				}
				close(cmd[i].fd[0]);
				if (i < nb_cmd - 1) {
					dup2(cmd[i].fd[1], STDOUT_FILENO);
				}
				close(cmd[i].fd[1]);
			}
			else if (cmd[i].final_input > REDIRECTION && cmd[i].final_output > REDIRECTION)
			{
				close(cmd[i].fd[0]);
				close(cmd[i].fd[1]);
				dup2(cmd[i].final_input, STDIN_FILENO);
				close (cmd[i].final_input);
				dup2(cmd[i].final_output, STDOUT_FILENO);
				close(cmd[i].final_output);
			}
			else if (cmd[i].final_input > REDIRECTION)
			{
				close(cmd[i].fd[0]);
				dup2(cmd[i].final_input, STDIN_FILENO);
				close (cmd[i].final_input);
				if (i < nb_cmd - 1) {
					dup2(cmd[i].fd[1], STDOUT_FILENO);
				}
					close (cmd[i].fd[1]);
			}
			else if (cmd[i].final_output > REDIRECTION)
			{
				if (i > 0)
				{
					dup2(cmd[i - 1].fd[0], STDIN_FILENO);
				}
				dup2(cmd[i].final_output, STDOUT_FILENO);
				close (cmd[i].final_output);
			}
			if (i > 0)
				close(cmd[i - 1].fd[0]);
			execve(cmd[i].path_cmd, cmd[i].args, cmd[i].env->envp);
			exit(1);
		}
		if (cmd[i].final_input < REDIRECTION && cmd[i].final_output < REDIRECTION)
		{
			close(cmd[i].fd[1]);

		}
		else if (cmd[i].final_input > REDIRECTION && cmd[i].final_output > REDIRECTION)
		{
			close(cmd[i].fd[1]);
			close (cmd[i].final_input);
			close(cmd[i].final_output);

		}
		else if (cmd[i].final_input > REDIRECTION)
		{
			close (cmd[i].fd[1]);
			close(cmd[i].final_input);
		} else if (cmd[i].final_output > REDIRECTION)
		{
			close(cmd[i].final_output);
			close(cmd[i].fd[1]);
		}
		if (i > 0) {
			close(cmd[i - 1].fd[0]);
		}
		i++;
	}
	close(cmd[i - 1].fd[0]);
	dprintf(2, "last fd a close = %d\n", cmd[i - 1].fd[0]);
	return (SUCCESS);
}
