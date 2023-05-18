#include "minishell.h"

void	ps_input_is_here_doc(const t_token *tok, t_cmd *cmd);

int	ps_get_input(t_token *tok, t_cmd *cmd, size_t index)
{
	while (tok)
	{
		if (tok->type == S_INPUT && tok->cmd_index == index)
		{
			if (cmd->input)
				free(cmd->input);
			cmd->input = NULL;
			cmd->input = f_strdup(tok->word);
			if (!cmd->input)
				return (CODE_MALLOC);
			cmd->type_in = tok->type;
			cmd->limiter = NULL;
			cmd->is_here_doc = 0;
			cmd->expand_here_doc = 0;
			cmd->final_input = open_input(cmd);
			if (cmd->final_input == ERROR_REDIRECT)
				return (ERROR);
		}
		else if (tok->type == D_INPUT && tok->cmd_index == index)
			ps_input_is_here_doc(tok, cmd);
		tok = tok->next;
	}
	return (SUCCESS);
}

void	ps_input_is_here_doc(const t_token *tok, t_cmd *cmd)
{
	if (cmd->input)
		free(cmd->input);
	cmd->input = NULL;
	cmd->type_in = tok->type;
	cmd->is_here_doc = 1;
	if (tok->quote == 0)
		cmd->expand_here_doc = 1;
}

int	ps_get_output_loop(t_token *tok, t_cmd *cmd, size_t index)
{
	if (tok->type == S_OUTPUT && tok->cmd_index == index)
	{
		if (cmd->output)
			free(cmd->output);
		cmd->output = NULL;
		cmd->output = strdup(tok->word);
		if (!cmd->output)
			return (CODE_MALLOC);
		cmd->type_out = tok->type;
		cmd->final_output = open_output(cmd);
	}
	else if (tok->type == D_OUTPUT && tok->cmd_index == index)
	{
		if (cmd->output)
			free(cmd->output);
		cmd->output = NULL;
		cmd->output = f_strdup(tok->word);
		if (!cmd->output)
			return (CODE_MALLOC);
		cmd->type_out = tok->type;
		cmd->final_output = open_output(cmd);
	}
	if (cmd->final_output == ERROR_REDIRECT)
		return (ERROR);
	return (SUCCESS);
}

int	ps_get_output(t_token *tok, t_cmd *cmd, size_t index)
{
	int	check;

	while (tok)
	{
		check = ps_get_output_loop(tok, cmd, index);
		if (check == CODE_MALLOC)
			return (CODE_MALLOC);
		if (check == ERROR)
			return (ERROR);
		tok = tok->next;
	}
	return (SUCCESS);
}
