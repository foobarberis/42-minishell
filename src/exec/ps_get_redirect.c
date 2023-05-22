#include "minishell.h"

void	ps_input_is_here_doc(t_token tok, t_cmd *cmd);

int	ps_get_input(t_token *tok, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (tok[i].word[i])
	{
		if (tok[i].type == S_INPUT)
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
			cmd->final_input = open_input(cmd);
			if (cmd->final_input == ERROR_REDIRECT)
				return (ERROR);
		}
		else if (tok[i].type == D_INPUT)
			ps_input_is_here_doc(tok[i], cmd);
		i++;
	}
	return (SUCCESS);
}

void	ps_input_is_here_doc(t_token tok, t_cmd *cmd)
{
	if (cmd->input)
		free(cmd->input);
	cmd->input = NULL;
	cmd->type_in = tok.type;
	cmd->is_here_doc = 1;
}

int	ps_get_output_loop(t_token tok, t_cmd *cmd)
{
	if (tok.type == S_OUTPUT)
	{
		if (cmd->output)
			free(cmd->output);
		cmd->output = NULL;
		cmd->output = strdup(tok.word);
		if (!cmd->output)
			return (CODE_MALLOC);
		cmd->type_out = tok.type;
		cmd->final_output = open_output(cmd);
	}
	else if (tok.type == D_OUTPUT)
	{
		if (cmd->output)
			free(cmd->output);
		cmd->output = NULL;
		cmd->output = f_strdup(tok.word);
		if (!cmd->output)
			return (CODE_MALLOC);
		cmd->type_out = tok.type;
		cmd->final_output = open_output(cmd);
	}
	if (cmd->final_output == ERROR_REDIRECT)
		return (ERROR);
	return (SUCCESS);
}

int	ps_get_output(t_token *tok, t_cmd *cmd)
{
	int	i;
	int	check;

	i = 0;
	while (tok->word[i])
	{
		check = ps_get_output_loop(tok[i], cmd);
		if (check == CODE_MALLOC)
			return (CODE_MALLOC);
		if (check == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
