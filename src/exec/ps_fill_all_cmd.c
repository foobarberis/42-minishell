#include "../inc/minishell.h"

void	init_to_null_cmd_struct(t_cmd *cmd)
{
	pipe(cmd->fd);
	cmd->error_redirect = 0;
	cmd->pid = -1;
	cmd->is_builtin = NONE;
	cmd->path_cmd = NULL;
	cmd->args = NULL;
	cmd->env = NULL;
	cmd->input = NULL;
	cmd->limiter = NULL;
	cmd->string_here_doc = NULL;
	cmd->output = NULL;
	cmd->final_output = -1;
	cmd->final_input = -1;
}

int	ps_fill_cmd_struct(t_cmd *cmd, t_token *tok, size_t index_cmd)
{
	int	nb_args;

	nb_args = count_type(tok, BASIC, BASIC, index_cmd) + 1;
	cmd->args = malloc(sizeof(char *) * nb_args);
	if (ps_get_args_cmd(tok, cmd->args, nb_args, index_cmd) == ERROR)
		return (ERROR);
	if (ps_get_path_cmd(cmd->args[0], cmd->env, &cmd->path_cmd) == ERROR)
		return (ERROR);
	ps_get_here_doc(tok, cmd, index_cmd);
	ps_get_input(tok, cmd, index_cmd);
	ps_get_output(tok, cmd, index_cmd);
	return (SUCCESS);
}

int	ps_initialisation_cmds(t_cmd *cmd, t_glb *glob)
{
	size_t	i;

	i = 0;
	while (i < glob->multiple_cmd)
	{
		init_to_null_cmd_struct(&cmd[i]);
		cmd[i].env = glob->environ;
		ps_fill_cmd_struct(&cmd[i], glob->tok[0], i);
		cmd[i].is_builtin = ps_is_builtin(cmd[i].args[0]);
		i++;
	}
	return (0);
}
