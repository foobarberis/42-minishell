/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:38:50 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/13 08:46:57 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parsing_rm_dollar_quote(t_token **tok)
{
	int	i;

	i = 0;
	while (tok[i])
	{
		if (tok[i + 1] && (*tok[i]->word == '$' && !tok[i]->quote)
			&& (*tok[i + 1]->word == '"' || *tok[i + 1]->word == '\''))
			token_array_rm(tok, i);
		i++;
	}
}

int	parsing_recreate_variables(t_token **tok)
{
	size_t	i;
	char	*tmp;

	i = 0;
	parsing_rm_dollar_quote(tok);
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

/**
 * @brief Delete duplicate whitespaces in a string. If the string contains
 * only whitespaces, return the empty string.
 * @param s
 * @return
 */
static char	*get_value_rm_whitespace(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (f_isspace(s[i]) && s[i] != ' ')
			s[i] = ' ';
		if (!f_isspace(s[i]) || (i > 0 && !f_isspace(s[i - 1])))
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
	return (s);
}

char	*get_value(char **env, char *key, int quote)
{
	char	*new;
	char	*getenv;

	getenv = env_getenv(env, key);
	if (*key == '?')
		return (f_itoa(g_rval));
	else if (!getenv)
		return (f_strdup(""));
	else
	{
		new = f_strdup(getenv);
		if (!new)
			return (NULL);
		if (quote != DOUBLE)
			return (get_value_rm_whitespace(new));
		else
			return (new);
	}
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
			value = get_value(env, &tok[i]->word[1], tok[i]->quote);
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
