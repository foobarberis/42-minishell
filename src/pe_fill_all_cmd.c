#include "../inc/execution.h"

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

int	ps_initialisation_cmds(t_cmd *cmd, t_glb *glob)
{
	int	i;

	i = 0;
	while (i < glob->multiple_cmd)
	{
		init_to_null_cmd_struct(&cmd[i]);
		cmd[i].env = glob->env;
		ps_fill_cmd_struct(&cmd[i], glob->tok[i]);
		cmd[i].builtin = ps_is_builtin(cmd[i].args[0]);
		ps_open_redirect(cmd[i].struct_input, \
		cmd[i].struct_output, &cmd[i].final_output, &cmd[i].final_input);
		i++;
	}
	return (0);
}
