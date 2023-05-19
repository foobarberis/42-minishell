#include "../inc/minishell.h"

void	ps_input_is_here_doc(const t_token *tok, t_cmd *cmd);

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

int	ps_get_args_cmd(t_token *tok, t_cmd *cmd, int nb_args, size_t index)
{
	int	i;

	i = 0;
	while (tok && i < nb_args)
	{
		if (tok->type == BASIC && tok->cmd_index == index)
		{
			cmd->args[i] = f_strdup(tok->word);
			if (!cmd->args[i] && tok->type == BASIC)
				return (CODE_MALLOC);
			i++;
		}
		tok = tok->next;
	}
	cmd->args[i] = NULL;
	if (i == 0)
		return (ERROR);
	return (SUCCESS);
}

int	ps_get_here_doc(t_token *tok, t_cmd *cmd, size_t index)
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
			if (!cmd->limiter)
				return (CODE_MALLOC);
			if (cmd->string_here_doc)
				free(cmd->string_here_doc);
			cmd->string_here_doc = here_doc(cmd->limiter);
			if (!cmd->string_here_doc)
				return (CODE_MALLOC);
		}
		tok = tok->next;
	}
	return (SUCCESS);
}
