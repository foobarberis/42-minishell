#include "../inc/execution.h"
#include "minishell.h"

int	fill_input_array(t_token *tok, t_input *input, int nb_input)
{
	while (tok)
	{
		if (tok->type == S_INPUT_CHEVRON)
		{
			tok = tok->next;
			input->type = tok->type;
			input->limiter = NULL;
			input->input = ft_strdup(tok->word);
			input->fd_input = nb_input;
			if (!input->input)
				return (ERROR);
			input++;
		}
		else if (tok->type == D_INPUT_CHEVRON)
		{
			tok = tok->next;
			input->input = NULL;
			input->type = tok->type;
			input->limiter = ft_strdup(tok->word);
			input->fd_input = nb_input;
			if (!input->input)
				return (ERROR);
			input++;
		}
		tok = tok->next;
	}
	return (SUCCESS);
}

int	fill_output_array(t_token *tok, t_output *output, int nb_output)
{
	while (tok)
	{
		if (tok->type == S_OUTPUT_CHEVRON)
		{
			tok = tok->next;
			output->output = strdup(tok->word);
			output->type = tok->type;
			output->fd_output = nb_output;
			if (!output->output)
				return (ERROR);
			output++;
		}
		else if (tok->type == D_OUTPUT_CHEVRON)
		{
			tok = tok->next;
			output->output = ft_strdup(tok->word);
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

int	fill_cmd_array(t_token *tok, char **cmd, int nb_args)
{
	int i;

	i = 0;
	while (tok && i < nb_args)
	{
		if (tok->type == BASIC)
		{
			cmd[i] = ft_strdup(tok->word);
			printf("tok-word = %s\n", tok->word);
			if (!cmd[i] && tok->type == BASIC)
				return (ERROR);
			i++;
		}
		tok = tok->next;
	}
	printf("i = %d\n", i);
	printf("cmd 0 first = %s.\n", cmd[0]);
	printf("cmd 1 second = %s.\n", cmd[1]);
	cmd[i] = NULL;
	printf("cmd 0 = %s.\n", cmd[0]);
	printf("cmd 1 = %s.\n", cmd[1]);
	return (SUCCESS);
}