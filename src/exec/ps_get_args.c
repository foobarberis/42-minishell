/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:09:38 by vburton           #+#    #+#             */
/*   Updated: 2023/05/30 14:09:39 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_type(t_token **tok, int type)
{
	int	i;
	int	nb_redirect;

	i = 0;
	nb_redirect = 0;
	while (tok[i])
	{
		if (tok[i]->type == type)
			nb_redirect++;
		i++;
	}
	return (nb_redirect);
}

int	ps_get_args_cmd(t_token **tok, t_cmd *cmd)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (tok[i])
	{
		if (tok[i]->type == BASIC)
		{
			cmd->args[y] = f_strdup(tok[i]->word);
			if (!cmd->args[y])
				return (CODE_MALLOC);
			y++;
		}
		i++;
	}
	cmd->args[y] = NULL;
	if (y == 0)
		return (ERROR);
	return (SUCCESS);
}
