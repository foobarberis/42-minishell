#include "../inc/execution.h"
#include "minishell.h"

void	init_to_null_cmd_struct(t_cmd *cmd)
{
	pipe(cmd->fd);
	cmd->pid = -1;
	cmd->builtin = NONE;
	cmd->path_cmd = NULL;
	cmd->args = NULL;
	cmd->env = NULL;
	cmd->struct_input = NULL;
	cmd->struct_output = NULL;
	cmd->final_output = -1;
	cmd->final_input = -1;

}

int initialisation_cmds(t_cmd *cmd, t_glb *glob)
{
	int i;

	i = 0;
	while (i < glob->multiple_cmd)
	{
		init_to_null_cmd_struct(&cmd[i]);
		cmd[i].env = glob->env;
		fill_cmd_struct(&cmd[i], glob->tok[i]);
		cmd[i].builtin = is_builtin(cmd[i].args[0]);
		open_all_redirects(cmd[i].struct_input, cmd[i].struct_output, &cmd[i].final_output, &cmd[i].final_input);
		if (cmd[i].struct_input && cmd[i].struct_input->fd_input > 0)
			close(cmd[i].fd[0]);
		if (cmd[i].struct_output && cmd[i].struct_output->fd_output > 0)
			close(cmd[i].fd[1]);
//		cmd[i].builtin = is_builtin(cmd->cmd[0]);
		i++;
	}
	return (0);
}
