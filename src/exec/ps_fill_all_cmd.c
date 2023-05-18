#include "../inc/minishell.h"

void	init_to_null_cmd_struct(t_cmd *cmd)
{
	cmd->is_valid = 0;
	cmd->pid = -1;
	cmd->is_builtin = NONE;
	cmd->path_cmd = NULL;
	cmd->args = NULL;
	cmd->env = NULL;
	cmd->input = NULL;
	cmd->limiter = NULL;
	cmd->is_here_doc = 0;
	cmd->expand_here_doc = 0;
	cmd->string_here_doc = NULL;
	cmd->output = NULL;
	cmd->final_output = -1;
	cmd->final_input = -1;
}

int	ps_check_redirect_n_blt(t_cmd *cmd, t_token *tok, int index_cmd, int *error)
{
	int	check_input;
	int	check_output;

	check_input = ps_get_input(tok, cmd, index_cmd);
	if (check_input == CODE_MALLOC)
		return (CODE_MALLOC);
	else if (check_input == ERROR)
		*error = 1;
	check_output = ps_get_output(tok, cmd, index_cmd);
	if (check_output == CODE_MALLOC)
		return (CODE_MALLOC);
	else if (check_output == ERROR)
		*error = 1;
	cmd->is_builtin = ps_is_builtin(cmd->args[0]);
	if (cmd->is_builtin == 0)
		cmd->path_cmd = ps_get_path_cmd(cmd->args[0], cmd->env, cmd->path_cmd);
	if (cmd->path_cmd && f_strcmp(cmd->path_cmd, ERR_MALLOC) == 0)
		return (cmd->path_cmd = NULL, CODE_MALLOC);
	return (SUCCESS);
}

int	ps_fill_cmd_struct(t_cmd *cmd, t_token *tok, int index_cmd)
{
	int	nb_args;
	int	error;
	int	args;
	int	check_middle;

	error = 0;
	nb_args = count_type(tok, BASIC, BASIC, index_cmd) + 1;
	cmd->args = malloc(sizeof(char *) * nb_args);
	if (!cmd->args)
		return (CODE_MALLOC);
	args = ps_get_args_cmd(tok, cmd, nb_args, index_cmd);
	if (args == CODE_MALLOC)
		return (CODE_MALLOC);
	else if (args == ERROR)
		error = 2;
	if (ps_get_here_doc(tok, cmd, index_cmd) == CODE_MALLOC)
		return (CODE_MALLOC);
	check_middle = ps_check_redirect_n_blt(cmd, tok, index_cmd, &error);
	if (check_middle == CODE_MALLOC)
		return (CODE_MALLOC);
	if (!cmd->is_builtin && cmd->path_cmd == NULL)
		error = 127;
	if (error == 0)
		return (SUCCESS);
	return (error);
}

int	ps_initialisation_cmds(t_cmd *cmd, t_glb *glob)
{
	int	i;

	i = 0;
	while (i < glob->multiple_cmd)
	{
		pipe(cmd[i].fd);
		init_to_null_cmd_struct(&cmd[i]);
		i++;
	}
	i = 0;
	while (i < glob->multiple_cmd)
	{
		cmd[i].glb = glob;
		cmd[i].env = glob->env;
		cmd[i].is_valid = ps_fill_cmd_struct(&cmd[i], glob->tok[0], i);
		if (cmd[i].is_valid == CODE_MALLOC || (cmd[i].is_here_doc && \
												cmd[i].string_here_doc == NULL))
			panic(cmd->glb, CODE_MALLOC, cmd);
		if (cmd[i].is_valid == 127 && (access(cmd[i].args[0], F_OK) == 0) && \
										(access(cmd[i].args[0], X_OK) != 0))
			cmd[i].is_valid = 126;
		i++;
	}
	return (0);
}
