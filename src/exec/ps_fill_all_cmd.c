#include "../inc/minishell.h"

void	init_to_null_cmd_struct(t_cmd *cmd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		pipe(cmd[i].fd);
		cmd[i].is_valid = 0;
		cmd[i].pid = -1;
		cmd[i].is_builtin = NONE;
		cmd[i].path_cmd = NULL;
		cmd[i].args = NULL;
		cmd[i].env = NULL;
		cmd[i].input = NULL;
		cmd[i].is_here_doc = 0;
		cmd[i].string_here_doc = NULL;
		cmd[i].output = NULL;
		cmd[i].final_output = -1;
		cmd[i].final_input = -1;
		i++;
	}
}

int	ps_check_redirect_n_blt(t_cmd *cmd, t_token **tok, int *error)
{
	int	check_input;
	int	check_output;

	check_input = ps_get_input(tok, cmd);
	if (check_input == CODE_MALLOC)
		return (CODE_MALLOC);
	else if (check_input == ERROR)
		return (*error = 1, ERROR);
	check_output = ps_get_output(tok, cmd);
	if (check_output == CODE_MALLOC)
		return (CODE_MALLOC);
	else if (check_output == ERROR)
		return (*error = 1, ERROR);
	cmd->is_builtin = ps_is_builtin(cmd->args[0]);
	if (cmd->is_builtin == 0)
		cmd->path_cmd = ps_get_path_cmd(cmd->args[0], cmd->env, cmd->path_cmd);
	if (cmd->path_cmd && f_strcmp(cmd->path_cmd, ERR_MALLOC) == 0)
		return (cmd->path_cmd = NULL, CODE_MALLOC);
	return (SUCCESS);
}

int	ps_fill_cmd_struct(t_cmd *cmd, t_token **tok)
{
	int	nb_args;
	int	error;
	int	args;
	int	check_middle;

	error = 0;
	nb_args = count_type(tok, BASIC) + 1;
	cmd->args = malloc(sizeof(char *) * nb_args);
	if (!cmd->args)
		return (CODE_MALLOC);
	args = ps_get_args_cmd(tok, cmd);
	if (args == CODE_MALLOC)
		return (CODE_MALLOC);
	else if (args == ERROR)
		error = 2;
	check_middle = ps_check_redirect_n_blt(cmd, tok, &error);
	if (check_middle == CODE_MALLOC)
		return (CODE_MALLOC);
	if (check_middle == ERROR)
		return (error);
	if (!cmd->is_builtin && cmd->path_cmd == NULL && error == 0)
		error = 127;
	if (error == 0)
		return (SUCCESS);
	return (error);
}

int	ps_initialisation_cmds(t_cmd *cmd, t_glb *glob)
{
	int	i;

	i = 0;
	init_to_null_cmd_struct(cmd, glob->multiple_cmd);
	while (i < glob->multiple_cmd)
	{
		cmd[i].glb = glob;
		cmd[i].env = glob->env;
		cmd[i].is_valid = ps_fill_cmd_struct(&cmd[i], glob->split[i]);
		if (cmd[i].is_valid == CODE_MALLOC) //  FIXME: Remove this || (cmd[i].is_here_doc && cmd[i].string_here_doc == NULL))
			panic(cmd->glb, CODE_MALLOC, cmd);
		if (cmd[i].is_valid == 127 && (access(cmd[i].args[0], F_OK) == 0) && \
										(access(cmd[i].args[0], X_OK) != 0))
			cmd[i].is_valid = 126;
		i++;
	}
	return (0);
}
