/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:39:39 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/20 12:55:25 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Regroup words between quotes in one string */
int	parsing_group_words(t_token **tok)
{
	size_t i;
	char  *tmp;

	i = 0;
	while (tok[i])
	{
		while (tok[i + 1] && tok[i]->quote && (tok[i]->quote == tok[i + 1]->quote))
		{
			tmp = f_strjoin(tok[i]->word, tok[i+1]->word);
			if (!tmp)
				return (1);
			free(tok[i]->word);
			tok[i]->word = tmp;
			token_array_rm(tok, i + 1);
		}
		i++;
	}
	return (0);
}

int	parsing_recreate_words(t_token **tok)
{
	size_t i;
	char  *tmp;

	i = 0;
	while (tok[i])
	{
		while (tok[i + 1] && (tok[i]->word_index == tok[i + 1]->word_index))
		{
			tmp = f_strjoin(tok[i]->word, tok[i + 1]->word);
			if (!tmp)
				return (1);
			free(tok[i]->word);
			tok[i]->word = tmp;
			token_array_rm(tok, i + 1);
		}
		i++;
	}
	return (0);
}
