#include "execution.h"
#include "minishell.h"

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


void	init_cmd_struc(t_cmd *cmd)
{
	pipe(cmd->fd);
	cmd->pid = -1;
	cmd->builtin = NONE;
	cmd->path_cmd = NULL;
	cmd->cmd = NULL;
	cmd->env = NULL;
	cmd->input = NULL;
	cmd->output = NULL;
	
}

int	fill_cmd_struct(t_glob	glob)
{
	int		nb_args;
	int		nb_input;
	int		nb_output;
	t_cmd	cmd;

	init(&cmd);
	cmd.env = glob.env;
	nb_args = count_type(glob.tok, BASIC) + 1;
	cmd.cmd = malloc(sizeof(char *) * nb_args);
	if (fill_cmd_array(glob.tok, &cmd.cmd) == ERROR)
		return (ERROR);
	if (get_path_cmd(cmd.cmd[0], cmd.env, &cmd.path_cmd) == ERROR)
		return (ERROR);
	nb_input = count_type(glob.tok, R_INPUT);
	cmd.input = malloc(sizeof(t_input * nb_input));
	if (fill_input_array(glob.tok, cmd.input));
		return (ERROR);
	nb_output = count_type(glob.tok, R_OUPUT);
	cmd.output = malloc(sizeof(t_output * nb_output));
	if (fill_output_array(glob.tok, cmd.output));
		return (ERROR);
}