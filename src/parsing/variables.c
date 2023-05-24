/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:38:50 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/24 12:52:49 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_legal(int c)
{
	return (f_isalnum(c) || c == '_' || c == '?' || c == 0);
}

static int	parsing_recreate_variables(t_token **tok)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (tok[i])
	{
		while (tok[i + 1] && *tok[i]->word == '$' && is_legal(*tok[i + 1]->word)
			&& (tok[i]->word_index == tok[i + 1]->word_index)
			&& (tok[i]->quote == tok[i + 1]->quote))
		{
			tmp = f_strjoin(tok[i]->word, tok[i + 1]->word);
			if (!tmp)
				return (1);
			free(tok[i]->word);
			tok[i]->word = tmp;
			token_array_rm(tok, i + 1);
			if (tok[i]->word && *tok[i]->word == '$'
				&& (tok[i]->word[1] == '?' || tok[i]->word[1] == 0))
				break ;
		}
		i++;
	}
	return (0);
}

static char	*get_value(char **env, char *key)
{
	char	*getenv;

	getenv = env_getenv(env, key);
	if (*key == '?')
		return (f_itoa(g_rval));
	else if (!getenv)
		return (f_strdup(""));
	else
		return (f_strdup(getenv));
}

int	parsing_expand_variables(t_token **tok, char **env)
{
	size_t	i;
	char	*value;

	i = 0;
	if (parsing_recreate_variables(tok))
		return (1);
	while (tok[i])
	{
		if (*tok[i]->word == '$' && tok[i]->word[1] && tok[i]->quote != SIMPLE)
		{
			value = get_value(env, &tok[i]->word[1]);
			if (!value)
				return (1);
			if (!*value)
			{
				token_array_rm(tok, i);
				free(value);
				continue ;
			}
			free(tok[i]->word);
			tok[i]->word = value;
		}
		i++;
	}
	return (0);
}
