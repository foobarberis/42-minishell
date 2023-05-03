#include "../inc/execution.h"

int	count_type(t_token *tok, int type)
{
	int	nb_redirect;

	nb_redirect = 0;
	while (tok->next)
	{
		if (tok->type == type)
			nb_redirect++;
		if (tok->next)
			tok = tok->next;
	}
	if (tok->type == type)
			nb_redirect++;
	return (nb_redirect);
}

int	fill_cmd_struct(t_cmd *cmd, t_token *tok)
{
	int	nb_args;
	int nb_input;
	int nb_output;

	nb_args = count_type(tok, BASIC) + 1;
	cmd->args = malloc(sizeof(char *) * nb_args);
	if (fill_cmd_array(tok, cmd->args, nb_args) == ERROR)
		return (ERROR);
	if (get_path_cmd(cmd->args[0], cmd->env->envp, &cmd->path_cmd) == ERROR)
		return (ERROR);
	nb_input = count_type(tok, R_INPUT);
	if (nb_input > 0)
	{
		cmd->struct_input = malloc(sizeof(t_input) * nb_input);
		if (fill_input_array(tok, cmd->struct_input, nb_input))
			return (ERROR);
	}
	nb_output = count_type(tok, R_OUTPUT);
	if (nb_output > 0)
	{
		cmd->struct_output = malloc(sizeof(t_output) * nb_output);
		if (fill_output_array(tok, cmd->struct_output, nb_output))
			return (ERROR);
	}
	return (SUCCESS);
}