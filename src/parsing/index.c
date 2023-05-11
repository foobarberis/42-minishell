/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:30:51 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/11 10:31:52 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ps_token_list_update_quote_state(char c, int state)
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

void	ps_token_list_set_index_quote(t_token **tok)
{
	int		state;
	t_token	*curr;

	curr = *tok;
	state = NONE;
	while (curr)
	{
		if (state == NONE && (curr->word[0] == '\'' || curr->word[0] == '"'))
		{
			curr->quote = NONE;
			state = ps_token_list_update_quote_state(curr->word[0], state);
			curr = curr->next;
		}
		else
		{
			state = ps_token_list_update_quote_state(curr->word[0], state);
			curr->quote = state;
			curr = curr->next;
		}
	}
}

void	ps_token_list_set_index_cmd(t_token **tok)
{
	size_t	cmd;
	t_token	*curr;

	cmd = 0;
	curr = *tok;
	while (curr)
	{
		if (curr->word[0] == '|')
			cmd++;
		curr->cmd_index = cmd;
		curr = curr->next;
	}
}

void	ps_token_list_set_index_word(t_token **tok)
{
	bool	sep;
	size_t	word;
	t_token	*curr;

	word = 0;
	sep = false;
	curr = *tok;
	while (curr)
	{
		if ((ismeta(curr->word[0]) || f_isspace(curr->word[0])) && !sep)
		{
			sep = true;
			word++;
		}
		else if (!(ismeta(curr->word[0]) || f_isspace(curr->word[0])) && sep)
		{
			sep = false;
			word++;
		}
		curr->word_index = word;
		curr = curr->next;
	}
}

void	ps_token_list_update_index_word(t_token **tok)
{
	size_t	i;
	t_token	*curr;
	t_token	*next;

	if (!tok)
		return ;
	i = 0;
	curr = *tok;
	while (curr)
	{
		next = curr->next;
		curr->word_index += i;
		if (next && curr->word[0] == '|'
			&& (next->word[0] == '<' || next->word[0] == '>'))
			i++;
		curr = next;
	}
}
