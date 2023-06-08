/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:39:39 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/08 11:47:48 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_here_doc(t_token **tok, char **env)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (tok[i])
	{
		if (tok[i]->type == D_INPUT)
		{
			tmp = here_doc(tok[i]->word);
			if (tmp && !tok[i]->quote)
				tmp = here_doc_expand_variables(env, tmp);
			if (!tmp)
				return (1);
			free(tok[i]->word);
			tok[i]->word = tmp;
		}
		i++;
	}
	return (0);
}

int	parsing_recreate_words(t_token **tok)
{
	size_t	i;
	char	*tmp;

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
			tok[i]->quote = tok[i + 1]->quote;
			token_array_rm(tok, i + 1);
		}
		i++;
	}
	return (0);
}

int	parsing_recreate_strings(t_token **tok)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (tok[i])
	{
		while (tok[i + 1] && tok[i]->quote
			&& (tok[i]->quote == tok[i + 1]->quote)
			&& (tok[i]->type == tok[i + 1]->type))
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
