/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:30:51 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/13 11:50:00 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parsing_update_quote_state(char c, int state)
{
	if (c == '\'' && state == SIMPLE)
		state = NONE;
	else if (c == '"' && state == DOUBLE)
		state = NONE;
	else if (c == '\'' && state == NONE)
		state = SIMPLE;
	else if (c == '"' && state == NONE)
		state = DOUBLE;
	return (state);
}

void	parsing_set_index_quote(t_token **tok)
{
	size_t	i;
	int		state;

	i = 0;
	state = NONE;
	while (tok[i])
	{
		if (state == NONE && (*tok[i]->word == '\'' || *tok[i]->word == '"'))
		{
			tok[i]->quote = NONE;
			state = parsing_update_quote_state(*tok[i]->word, state);
		}
		else
		{
			state = parsing_update_quote_state(*tok[i]->word, state);
			tok[i]->quote = state;
		}
		i++;
	}
}

void	parsing_set_index_cmd(t_token **tok)
{
	size_t	i;
	size_t	cmd;

	i = 0;
	cmd = 0;
	while (tok[i])
	{
		if (!tok[i]->quote && *tok[i]->word == '|')
			cmd++;
		tok[i]->cmd_index = cmd;
		i++;
	}
}

void	parsing_set_index_word(t_token **tok)
{
	int		word;
	size_t	i;
	size_t	word_index;

	i = 0;
	word = 0;
	word_index = 0;
	while (tok[i])
	{
		if (!tok[i]->quote)
		{
			if (f_isspace(*tok[i]->word))
				word = 0;
			else if (!word)
			{
				word = 1;
				word_index++;
			}
		}
		tok[i]->word_index = word_index;
		i++;
	}
}

void	parsing_update_index_word(t_token **t)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (t[i])
	{
		t[i]->word_index += j;
		if (t[i + 1])
		{
			if (!t[i]->quote)
				if ((ismeta(*t[i]->word) && (!ismeta(*t[i + 1]->word)
							|| (ismeta(*t[i + 1]->word) && t[i + 1]->quote)))
					|| (!ismeta(*t[i]->word) && ismeta(*t[i + 1]->word)))
					j++;
			if ((t[i]->quote && ismeta(*t[i]->word))
				&& (!ismeta(*t[i + 1]->word)
					|| (ismeta(*t[i + 1]->word) && !t[i + 1]->quote)))
				j++;
			if (*t[i]->word == '|'
				&& (*t[i + 1]->word == '<' || *t[i + 1]->word == '>'))
				j++;
		}
		i++;
	}
}
