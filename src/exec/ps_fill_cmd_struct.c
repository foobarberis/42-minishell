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

int	ps_get_args_cmd(t_token *tok, char **cmd, int nb_args, size_t index)
{
	int	i;

	i = 0;
	while (tok && i < nb_args)
	{
		if (tok->type == BASIC && tok->cmd_index == index)
		{
			cmd[i] = f_strdup(tok->word);
			if (!cmd[i] && tok->type == BASIC)
				return (ERROR);
			i++;
		}
		tok = tok->next;
	}
	cmd[i] = NULL;
	if (i == 0)
		return (ERROR);
	return (SUCCESS);
}
void ps_get_here_doc(t_token *tok, t_cmd *cmd, size_t index)
{
	while (tok)
	{
		if (tok->type == D_INPUT && tok->cmd_index == index)
		{
			cmd->input = NULL;
			cmd->type_in = tok->type;
			cmd->is_here_doc = 1;
			cmd->final_input = 3;
			cmd->limiter = f_strdup(tok->word);
			if (cmd->string_here_doc)
				free(cmd->string_here_doc);
			here_doc(cmd->limiter, &cmd->string_here_doc);
		}
		tok = tok->next;
	}
}

int	ps_get_input(t_token *tok, t_cmd *cmd, size_t index)
{
	while (tok)
	{
		if (tok->type == S_INPUT && tok->cmd_index == index)
		{
			if (cmd->input)
				free(cmd->input);
			cmd->input = f_strdup(tok->word);
			cmd->type_in = tok->type;
			cmd->limiter = NULL;
			cmd->is_here_doc = 0;
			cmd->final_input = open_input(cmd);
			if (cmd->final_input == ERROR_REDIRECT)
				return (ERROR) ;
		}
		else if (tok->type == D_INPUT && tok->cmd_index == index)
		{
			if (cmd->input)
				free(cmd->input);
			cmd->input = NULL;
			cmd->type_in = tok->type;
			cmd->is_here_doc = 1;
		}
		tok = tok->next;
	}
	return (SUCCESS);
}

int	ps_get_output(t_token *tok, t_cmd *cmd, size_t index)
{
	while (tok)
	{
		if (tok->type == S_OUTPUT && tok->cmd_index == index)
		{
			if (cmd->output)
				free(cmd->output);
			cmd->output = strdup(tok->word);
			cmd->type_out = tok->type;
			cmd->final_output = open_output(cmd);
		}
		else if (tok->type == D_OUTPUT && tok->cmd_index == index)
		{
			if (cmd->output)
				free(cmd->output);
			cmd->output = f_strdup(tok->word);
			cmd->type_out = tok->type;
			cmd->final_output = open_output(cmd);
		}
		if (cmd->final_output == ERROR_REDIRECT)
			return (ERROR) ;
		tok = tok->next;
	}
	return (SUCCESS);
}
