#include "../inc/execution.h"

void	init_to_null_cmd_struct(t_cmd *cmd)
{
	pipe(cmd->fd);
	dprintf(2, "j'ouvre fd = %d\n", cmd->fd[0]);
	dprintf(2, "j'ouvre fd = %d\n", cmd->fd[1]);
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
		cmd[i].no_cmd = i;
		cmd[i].nb_tot_cmd = glob->multiple_cmd;
		init_to_null_cmd_struct(&cmd[i]);
		cmd[i].env = glob->env;
		fill_cmd_struct(&cmd[i], glob->tok[i]);
		cmd[i].builtin = is_builtin(cmd[i].args[0]);
		open_all_redirects(cmd[i].struct_input, cmd[i].struct_output, &cmd[i].final_output, &cmd[i].final_input);
		i++;
	}
	return (0);
}
