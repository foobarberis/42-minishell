#include "../inc/execution.h"
#include "../inc/minishell.h"

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
		if (cmd.final_input == NO_REDIRECTION)
			close(cmd.fd[0]);
		else
		{
			dup2(cmd.final_input, STDIN_FILENO);
			close(cmd.final_input);
		}
		cmd.pid = fork();
		if (cmd.pid == -1)
			perror(" :fork failed\n");
		if (cmd.pid == 0)
		{
			if (cmd.final_output == NO_REDIRECTION)
			{
				dup2(cmd.fd[1], STDOUT_FILENO);
				close(cmd.fd[1]);
			}
			else
			{
				dup2(cmd.final_output, STDOUT_FILENO);
				close(cmd.final_output);
			}
			if (cmd.final_input == NO_REDIRECTION)
				close(cmd.fd[0]);
			else
				close(cmd.final_input);
			execve(cmd.path_cmd, cmd.args, cmd.env->envp);
			//			ft_free(cmd.args, nb_cmd);
			exit(1);
		}
//	}
	return (SUCCESS);
}
