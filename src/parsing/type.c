/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:38:36 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/23 15:43:09 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_fill_type(t_token **tok)
{
	size_t	i;

	i = 0;
	while (tok[i])
	{
		if (!tok[i]->quote)
		{
			if (!tok[i + 1])
				break ;
			if (!f_strcmp(tok[i]->word, ">"))
				tok[i + 1]->type = S_OUTPUT;
			else if (!f_strcmp(tok[i]->word, "<"))
				tok[i + 1]->type = S_INPUT;
			else if (!f_strcmp(tok[i]->word, ">>"))
				tok[i + 1]->type = D_OUTPUT;
			else if (!f_strcmp(tok[i]->word, "<<"))
				tok[i + 1]->type = D_INPUT;
		}
		i++;
	}
}
