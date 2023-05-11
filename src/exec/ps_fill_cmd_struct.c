#include "../inc/minishell.h"

int	count_type(t_token *tok, int type1, int type2, size_t i)
{
	int	nb_redirect;

	nb_redirect = 0;
	while (tok)
	{
		if ((tok->type == type1 || tok->type == type2) && tok->cmd_index == i)
			nb_redirect++;
		tok = tok->next;
	}
	return (nb_redirect);
}

int	ps_fill_cmd_struct(t_cmd *cmd, t_token *tok, size_t i)
{
	int	nb_args;
	int	nb_output;

	nb_args = count_type(tok, BASIC, BASIC, i) + 1;
	cmd->args = malloc(sizeof(char *) * nb_args);
	if (ps_fill_args_array(tok, cmd->args, nb_args, i) == ERROR)
		return (ERROR);
	if (ps_get_path_cmd(cmd->args[0], cmd->env, &cmd->path_cmd) == ERROR)
		return (ERROR);
	cmd->nb_input = count_type(tok, S_INPUT, D_INPUT, i);
	if (cmd->nb_input > 0)
	{
		cmd->struct_input = malloc(sizeof(t_input) * cmd->nb_input);
		if (ps_fill_struct_input(tok, cmd->struct_input, cmd->nb_input, i))
			return (ERROR);
	}
	nb_output = count_type(tok, S_OUTPUT, D_OUTPUT, i);
	if (nb_output > 0)
	{
		cmd->struct_output = malloc(sizeof(t_output) * nb_output);
		if (ps_fill_struct_output(tok, cmd->struct_output, nb_output, i))
			return (ERROR);
	}
	return (SUCCESS);
}
