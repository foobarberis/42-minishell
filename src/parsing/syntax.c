/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:44:55 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/19 15:12:51 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ps_line_has_balanced_quotes(t_token **tok)
{
	t_token	*curr;
	size_t	nsimple;
	size_t	ndouble;

	curr = *tok;
	nsimple = 0;
	ndouble = 0;
	while (curr)
	{
		if (curr->word[0] == '"' && curr->quote == NONE)
			ndouble++;
		else if (curr->word[0] == '\'' && curr->quote == NONE)
			nsimple++;
		curr = curr->next;
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

static int which_error(t_token **tok, t_token *curr, t_token *next)
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

static int	check_syntax(t_token **tok)
{
	t_token	*next;
	t_token	*curr;

	curr = *tok;
	while (curr)
	{
		next = curr->next;
		if (ismeta(curr->word[0]) && curr->quote == NONE)
		{
			if (next && (check_further(curr->word[0], next->word[0]) == 1))
				next = next->next;
			if (next && (check_further(curr->word[0], next->word[0]) == 2))
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

bool ps_token_list_has_syntax_error(t_token **tok)
{
	int			r;
	static char	*token[6] = {"<", ">", "<<", ">>", "|", "newline"};

	r = 0;
	if (!ps_line_has_balanced_quotes(tok))
		return (true);
	r = check_syntax(tok);
	if (r != -1)
		return (f_dprintf(STDERR_FILENO, "minishell: syntax error near unexpected token `%s'\n", token[r]), true);
	return (false);
}
