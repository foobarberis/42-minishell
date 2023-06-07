/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:29:55 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/07 11:50:43 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_delete_space(t_token **tok)
{
	size_t	i;

	i = 0;
	while (tok[i])
	{
		if (!tok[i]->quote && f_isspace(tok[i]->word[0]))
			token_array_rm(tok, i);
		else
			i++;
	}
}

void	parsing_delete_pipe(t_token **tok)
{
	size_t	i;

	i = 0;
	while (tok[i])
	{
		if (tok[i]->quote == NONE && tok[i]->word[0] == '|')
			token_array_rm(tok, i);
		else
			i++;
	}
}

void	parsing_delete_quote(t_token **tok)
{
	size_t	i;

	i = 0;
	while (tok[i])
	{
		if (!tok[i]->quote && (*tok[i]->word == '\'' || *tok[i]->word == '"'))
		{
			if (tok[i + 1] && (*tok[i]->word == *tok[i + 1]->word))
				*tok[i++]->word = '\0';
			token_array_rm(tok, i);
		}
		else
			i++;
	}
}

void	parsing_delete_bracket(t_token **tok)
{
	size_t	i;

	i = 0;
	while (tok[i])
	{
		if (!tok[i]->quote && !tok[i]->type
			&& (*tok[i]->word == '<' || *tok[i]->word == '>'))
			token_array_rm(tok, i);
		else
			i++;
	}
}
