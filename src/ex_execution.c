#include "execution.h"
#include "minishell.h"

/* Penser avant la boucle readline a save stdin et stdout dans 2 variables
les dup2 pour leur redonner leur indice de depart a la fin d'une cmd si il y a eu une redirection*/
int	main_execution(t_glob data)
{
	if (data.multiple_cmd == NONE)
		single_exection(data.cmd);

}

int	single_execution(t_cmd *cmd)
{
	int	builtin;

	builtin = is_builtin(cmd->args[0])
	if (builtin != NONE)
	{
		if (cmd->output != NONE)
		{
			open_all_redirects(cmd->redirects);
			dup2(cmd->output, STDOUT_FILENO);
			close (cmd->output);
		}
		exec_builtin(builtin, cmd->args);
		dup2(save_stdout, STDOUT);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			perror(" :fork failed\n");
		if(pid == 0)
		{
			if (cmd->input != NULL)
			{
				dup2(cmd->input, STDIN_FILENO);
				close(cmd->input);
			}
			if (cmd->output != NULL)
			{
				dup2(cmd->output, STDOUT_FILENO);
				close(cmd->output);
			}
			execve(cmd->args[0], cmd->args, cmd->env);
			ft_free();
			exit(0);
		}
	}
	return ;
}