/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:44:55 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/12 13:59:56 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parsing_check_quotes(t_token **tok)
{
	size_t	i;
	size_t	nsimple;
	size_t	ndouble;

	i = 0;
	nsimple = 0;
	ndouble = 0;
	while (tok[i])
	{
		if (tok[i]->word[0] == '"' && !tok[i]->quote)
			ndouble++;
		else if (tok[i]->word[0] == '\'' && !tok[i]->quote)
			nsimple++;
		i++;
	}
	if (nsimple % 2)
		return (f_dprintf(STDERR_FILENO, ERR_SYNTAX, "\'"), 1);
	else if (ndouble % 2)
		return (f_dprintf(STDERR_FILENO, ERR_SYNTAX, "\""), 1);
	return (0);
}

static int	check_syntax_newline(t_token **tok)
{
	size_t	i;

	i = 0;
	while (tok[i])
		i++;
	if (i && !tok[i - 1]->quote && ismeta(*tok[i - 1]->word))
		return (1);
	return (0);
}

static int	check_syntax_pipes(t_token **tok)
{
	size_t	i;

	i = 0;
	while (tok[i])
	{
		if (!tok[i]->quote && *tok[i]->word == '|')
		{
			if (!i)
				return (1);
			if (ismeta(*tok[i - 1]->word))
				return (1);
			if (tok[i + 1] && *tok[i + 1]->word == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

static int	check_syntax_brackets(t_token **tok)
{
	size_t	i;

	i = 0;
	while (tok[i])
	{
		if (!tok[i]->quote && tok[i + 1]
			&& !tok[i + 1]->quote
			&& (*tok[i]->word == '<' || *tok[i]->word == '>'))
		{
			if ((*tok[i]->word == *tok[i + 1]->word)
				&& (tok[i]->word_index != tok[i + 1]->word_index))
				return (f_dprintf(2, ERR_SYNTAX, tok[i + 1]->word), 1);
			if (*tok[i]->word == '>' && *tok[i + 1]->word == '<')
				return (f_dprintf(2, ERR_SYNTAX, "<"), 1);
			if ((*tok[i]->word == *tok[i + 1]->word)
				|| (*tok[i]->word == '<' && *tok[i + 1]->word == '>'))
				i++;
			if (tok[i]->quote || tok[i + 1]->quote)
				continue ;
			if (*tok[i + 1]->word == '<' || *tok[i + 1]->word == '>')
				return (f_dprintf(2, ERR_SYNTAX, tok[i + 1]->word), 1);
		}
		i++;
	}
	return (0);
}

int	parsing_check_syntax(t_token **tok)
{
	if (parsing_check_quotes(tok))
		return (g_rval = 2, 1);
	if (check_syntax_newline(tok))
		return (g_rval = 2, f_dprintf(STDERR_FILENO, ERR_SYNTAX, "newline"), 1);
	if (check_syntax_pipes(tok))
		return (g_rval = 2, f_dprintf(STDERR_FILENO, ERR_SYNTAX, "|"), 1);
	if (check_syntax_brackets(tok))
		return (g_rval = 2, 1);
	return (0);
}
