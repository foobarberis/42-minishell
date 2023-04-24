#include "../inc/execution.h"
#include "minishell.h"

int	fill_input_array(t_token tok, t_input *input)
{
	while (tok->word)
	{
		if (tok->type == S_INPUT_CHEVRON)
		{
			tok++;
			input->type = tok->type;
			input->limiteur = NULL;
			input->input = ft_strdup(tok->word);
			if (!input->input)
				return (ERROR);
		}
		else if (tok->type == D_INPUT_CHEVRON)
		{
			tok++;
			input->input = NULL;
			input->type = tok->type;
			input->limiteur = ft_strdup(tok->word);
			if (!input->input)
				return (ERROR);
		}
		tok++;
	}
	return (SUCCESS);
}

int	fill_output_array(t_token tok, t_output *output)
{
	while (tok->word)
	{
		if (tok->type == S_OUTPUT_CHEVRON)
		{
			tok++;
			output->output = ft_strdup(tok->word);
			output->type = tok->type;
			if (!output->output)
				return (ERROR);
		}
		else if (tok->type == D_OUTPUT_CHEVRON)
		{
			tok++;
			output->output = ft_strdup(tok->word);
			output->type = tok->type;
			if (!output->output)
				return (ERROR);
		}
		tok++;
	}
	return (SUCCESS);
}

int	fill_cmd_array(t_token tok, char ***cmd)
{
	int	i;

	i = 0;
	while (tok->word)
	{
		if (tok->type == BASIC)
			cmd[i] = ft_stdup(tok->word);
		if (!cmd[i])
			return (ERROR);
		i++;
	}
	cmd[i] = NULL;
	return (SUCCESS);
}