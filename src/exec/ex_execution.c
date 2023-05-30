#include "../inc/minishell.h"

static void	child_exec(t_glb *glb, t_cmd *cmd, size_t i, size_t nb_cmd)
{
	if (cmd[i].is_valid)
		exit(cmd[i].is_valid);
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
	if (cmd[i].is_builtin)
		ex_builtin(glb, cmd, cmd[i].is_builtin, cmd[i].args);
	else
		execve(cmd[i].path_cmd, cmd[i].args, cmd[i].env);
}

static void	parent_exec(t_cmd *cmd, size_t i)
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

static void	ex_childs(t_glb *glb, t_cmd *cmd, size_t i, size_t nb_cmd)
{
	int	pid;

	pid = fork();
	cmd[i].pid = pid;
	if (pid == -1)
		perror(" :fork failed\n");
	if (pid == 0)
	{
		g_rval = (uint8_t)cmd[i].is_valid;
		child_exec(glb, cmd, i, nb_cmd);
		if (i > 0)
			close (cmd[i - 1].fd[0]);
		panic(glb, g_rval, cmd);
	}
	parent_exec(cmd, i);
}

static int	ex_launch(t_glb *glb, t_cmd *cmd, size_t nb_cmd)
{
	size_t	i;

	i = 0;
	if (nb_cmd == 1 && (cmd[i].is_builtin == EXPORT || cmd[i].is_builtin == UNSET || cmd[i].is_builtin == EXIT || cmd[i].is_builtin == CD))
	{
		child_exec(glb, cmd, i, nb_cmd);
		i++;
	}
	while (i < nb_cmd && nb_cmd >= 1)
	{
		while (i < nb_cmd && cmd[i].is_valid > 0)
		{
			g_rval = (uint8_t)cmd[i].is_valid;
			parent_exec(cmd, i);
			i++;
		}
		if (i == nb_cmd)
			break ;
		ex_childs(glb, cmd, i, nb_cmd);
		i++;
	}
	if (i > 0 && cmd[i - 1].fd[0])
		close(cmd[i - 1].fd[0]);
	return (SUCCESS);
}

int	exec(t_glb *glb)
{
	int		status;
	int		i;
	t_cmd	*cmd;

	i = 0;
	status = 0;
	glb->multiple_cmd = (int)get_max_cmd(glb->tok);
	cmd = malloc(sizeof(t_cmd) * glb->multiple_cmd);
	if (!cmd)
		return (0);
	ps_initialisation_cmds(cmd, glb);
	ex_launch(glb, &cmd[i], glb->multiple_cmd);
	while (i < glb->multiple_cmd)
	{
		waitpid(cmd[i].pid, &status, 0);
		if (WIFEXITED(status) && cmd[i].is_valid == 0 && cmd[i].pid != -1)
			g_rval = (uint8_t)WEXITSTATUS(status);
		i++;
	}
	close_fd(cmd, glb->multiple_cmd);
	free_t_cmd(cmd, glb->multiple_cmd);
	return (0);
}
