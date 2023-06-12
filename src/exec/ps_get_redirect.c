/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_get_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:12:47 by vburton           #+#    #+#             */
/*   Updated: 2023/06/09 18:31:24 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ps_input_is_here_doc(t_cmd *cmd, char *here_doc)
{
	if (cmd->input)
		free(cmd->input);
	cmd->input = NULL;
	cmd->type_in = D_INPUT;
	cmd->is_here_doc = 1;
	cmd->final_input = 1;
	cmd->string_hc = here_doc;
}

static int	ps_get_input(t_token *tok, t_cmd *cmd)
{
	if (tok->type == S_INPUT)
	{
		if (cmd->input)
			free(cmd->input);
		cmd->input = NULL;
		cmd->input = f_strdup(tok->word);
		if (!cmd->input)
			return (CODE_MALLOC);
		cmd->type_in = S_INPUT;
		cmd->is_here_doc = 0;
		cmd->final_input = open_input(cmd);
		if (cmd->final_input == ERROR_REDIRECT)
			return (ERROR);
	}
	else if (tok->type == D_INPUT)
		ps_input_is_here_doc(cmd, tok->word);
	return (SUCCESS);
}

static int	ps_get_output_loop(t_token *tok, t_cmd *cmd)
{
	if (tok->type == S_OUTPUT)
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
	else if (tok->type == D_OUTPUT)
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

static int	ps_get_output(t_token *tok, t_cmd *cmd)
{
	int	check;

	check = ps_get_output_loop(tok, cmd);
	if (check == CODE_MALLOC)
		return (CODE_MALLOC);
	if (check == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ps_get_redirect(t_token **tok, t_cmd *cmd)
{
	int	i;
	int	input;
	int	output;

	i = 0;
	while (tok[i])
	{
		output = ps_get_output(tok[i], cmd);
		if (output == CODE_MALLOC)
			return (CODE_MALLOC);
		if (output == ERROR)
			return (ERROR);
		input = ps_get_input(tok[i], cmd);
		if (input == CODE_MALLOC)
			return (CODE_MALLOC);
		if (input == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
