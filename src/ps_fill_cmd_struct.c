#include "../inc/execution.h"
#include "../inc/minishell.h"

int	count_type(t_tok *tok, int	type)
{
	int	nb_redirect;

	nb_redirect = 0;
	while (tok->word)
	{
		if (tok->type == type)
			nb_redirect++;
		tok++;
	}
	return (nb_redirect);
}


void	init_cmd_struct(t_cmd *cmd)
{
	pipe(cmd->fd);
	cmd->pid = -1;
	cmd->builtin = NONE;
	cmd->path_cmd = NULL;
	cmd->cmd = NULL;
	cmd->env = NULL;
	cmd->struct_input = NULL;
	cmd->struct_output = NULL;
	cmd->final_output = NULL;
	cmd->final_input = NULL;
	
}

int	fill_cmd_struct(t_glob	glob)
{
	int 	i;
	int		nb_args;
	int		nb_input;
	int		nb_output;
	t_cmd	*cmd;

	i = 0;
	cmd = malloc(sizeof(t_cmd) * glob.multiple_cmd);
	while (i < glob.multiple_cmd)
	{
		init_cmd_struct(&cmd[i]);
		cmd[i].env = glob.env;
		nb_args = count_type(glob.tok[i], BASIC) + 1;
		cmd[i].cmd = malloc(sizeof(char *) * nb_args);
		if (fill_cmd_array(glob.tok[i], &cmd[i].cmd) == ERROR)
			return (ERROR);
		if (get_path_cmd(cmd[i].cmd[0], cmd[i].env->envp, &cmd[i].path_cmd) == ERROR)
			return (ERROR);
		nb_input = count_type(glob.tok[i], R_INPUT);
		cmd[i].input = malloc(sizeof(t_input) * nb_input);
		if (fill_input_array(glob.tok[i], cmd[i].input))
			return (ERROR);
		nb_output = count_type(glob.tok[i], R_OUPUT);
		cmd[i].output = malloc(sizeof(t_output) * nb_output);
		if (fill_output_array(glob.tok[i], cmd[i].output))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}