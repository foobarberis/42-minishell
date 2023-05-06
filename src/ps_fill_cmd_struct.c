#include "../inc/minishell.h"

int	count_type(t_token *tok, int type1, int type2)
{
	int	nb_redirect;

	nb_redirect = 0;
	while (tok)
	{
		if (tok->type == type1 || tok->type == type2)
			nb_redirect++;
		tok = tok->next;
	}
	if (tok && (tok->type == type1 || tok->type == type2))
		nb_redirect++;
	return (nb_redirect);
}

int	ps_fill_cmd_struct(t_cmd *cmd, t_token *tok)
{
	int	nb_args;
	int	nb_input;
	int	nb_output;

	nb_args = count_type(tok, BASIC, BASIC) + 1;
	cmd->args = malloc(sizeof(char *) * nb_args);
	if (ps_fill_args_array(tok, cmd->args, nb_args) == ERROR)
		return (ERROR);
	if (ps_get_path_cmd(cmd->args[0], cmd->env, &cmd->path_cmd) == ERROR)
		return (ERROR);
	nb_input = count_type(tok, S_INPUT, D_INPUT);
	if (nb_input > 0)
	{
		cmd->struct_input = malloc(sizeof(t_input) * nb_input);
		if (ps_fill_struct_input(tok, cmd->struct_input, nb_input))
			return (ERROR);
	}
	nb_output = count_type(tok, S_OUTPUT, D_OUTPUT);
	if (nb_output > 0)
	{
		cmd->struct_output = malloc(sizeof(t_output) * nb_output);
		if (ps_fill_struct_output(tok, cmd->struct_output, nb_output))
			return (ERROR);
	}
	return (SUCCESS);
}
