#include "../inc/minishell.h"
#include "minishell.h"

int	ps_fill_struct_input(t_token *tok, t_input *input, int nb_input, size_t index)
{
	while (tok)
	{
		if (tok->type == S_INPUT && tok->cmd_index == index)
		{
			input->type = tok->type;
			input->limiter = NULL;
			input->is_here_doc = 0;
			input->string_here_doc = NULL;
			input->input = f_strdup(tok->word);
			input->fd_input = nb_input;
			if (!input->input)
				return (ERROR);
			input++;
		}
		else if (tok->type == D_INPUT && tok->cmd_index == index)
		{
			input->input = NULL;
			input->type = tok->type;
			input->is_here_doc = 1;
			input->string_here_doc = NULL;
			input->limiter = f_strdup(tok->word);
			input->fd_input = nb_input;
			if (!input->limiter)
				return (ERROR);
			input++;
		}
		tok = tok->next;
	}
	return (SUCCESS);
}

int	ps_fill_struct_output(t_token *tok, t_output *output, int nb_output, size_t index)
{
	while (tok)
	{
		if (tok->type == S_OUTPUT && tok->cmd_index == index)
		{
			output->output = strdup(tok->word);
			output->type = tok->type;
			output->fd_output = nb_output;
			if (!output->output)
				return (ERROR);
			output++;
		}
		else if (tok->type == D_OUTPUT && tok->cmd_index == index)
		{
			output->output = f_strdup(tok->word);
			output->type = tok->type;
			output->fd_output = nb_output;
			if (!output->output)
				return (ERROR);
			output++;
		}
		tok = tok->next;
	}
	return (SUCCESS);
}

int	ps_fill_args_array(t_token *tok, char **cmd, int nb_args, size_t index)
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
	return (SUCCESS);
}
