/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:44:55 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/20 12:53:46 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	parsing_check_quotes(t_token **tok)
{
	size_t i;
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
		return (f_dprintf(STDERR_FILENO, "minishell: syntax error near unexpected token `\''\n"), false);
	else if (ndouble % 2)
		return (f_dprintf(STDERR_FILENO, "minishell: syntax error near unexpected token `\"'\n"), false);
	return (true);
}

static int	check_further(int a, int b)
{
	if ((a == '>' && b == '>') || (a == '<' && b == '<'))
		return (1);
	if ((a == '|' && b == '<') || (a == '|' && b == '>'))
		return (2);
	return (0);
}

static int which_error(t_token *curr, t_token *next)
{
	if (!next && curr->word[0] != '|')
		return (5);
	else if (!next && curr->word[0] == '|')
		return (4);
	else if (curr->word[0] == '>' && next->word[0] == '>')
		return (3);
	else if (curr->word[0] == '<' && next->word[0] == '<')
		return (2);
	else if (curr->word[0] == '>' && next->word[0] == '<')
		return (0);
	else if (curr->word[0] == '<' && next->word[0] == '>')
		return (5);
	else
		return (4);
}

/* static int	check_syntax(t_token **tok)
{
	size_t i;

	i = 0;
	while (tok[i])
	{
		if (ismeta(tok[i]->word[0]) && !tok[i]->quote)
		{
			if (tok[i + 1] && (check_further(*tok[i]->word, next->word[0]) == 1))
				next = next->next;
			if (tok[i + 1] && (check_further(*tok[i]->word, next->word[0]) == 2))
			{
				next = next->next;
				if (next && (curr->next->word[0] == next->word[0]))
					next = next->next;
			}
			if (!next || ismeta(next->word[0]))
				return (which_error(tok, curr, next));
		}
		curr = next;
	}
	return (-1);
}
 */
bool parsing_check_syntax(t_token **tok)
{
	int			r;
	static char	*token[6] = {"<", ">", "<<", ">>", "|", "newline"};

	r = 0;
	if (!parsing_check_quotes(tok))
		return (true);
	// r = check_syntax(tok);
	if (r != -1)
		return (f_dprintf(STDERR_FILENO, "minishell: syntax error near unexpected token `%s'\n", token[r]), true);
	return (false);
}
