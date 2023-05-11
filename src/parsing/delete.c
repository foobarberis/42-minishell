/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:29:55 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/11 10:30:33 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ps_token_list_delete_space(t_token **tok)
{
	t_token	*next;
	t_token	*curr;

	curr = *tok;
	while (curr)
	{
		next = curr->next;
		if (curr->quote == NONE && f_isspace(curr->word[0]))
			ps_token_list_node_rm(tok, curr);
		curr = next;
	}
}

void	ps_token_list_delete_quote(t_token **tok)
{
	t_token	*next;
	t_token	*curr;

	curr = *tok;
	while (curr)
	{
		next = curr->next;
		if (curr->quote == NONE
			&& (curr->word[0] == '\'' || curr->word[0] == '"'))
		{
			if (next && (curr->word[0] == next->word[0]))
			{
				curr->word[0] = 0;
				next = next->next;
				ps_token_list_node_rm(tok, curr->next);
			}
			else
				ps_token_list_node_rm(tok, curr);
		}
		curr = next;
	}
}

void	ps_token_list_delete_bracket(t_token **tok)
{
	t_token	*next;
	t_token	*curr;

	curr = *tok;
	while (curr)
	{
		next = curr->next;
		if (curr->quote == NONE && curr->type == BASIC
			&& (curr->word[0] == '<' || curr->word[0] == '>'))
			ps_token_list_node_rm(tok, curr);
		curr = next;
	}
}

void	ps_token_list_delete_pipe(t_token **tok)
{
	t_token	*next;
	t_token	*curr;

	curr = *tok;
	while (curr)
	{
		next = curr->next;
		if (next && curr->quote == NONE && curr->word[0] == '|')
			ps_token_list_node_rm(tok, curr);
		curr = next;
	}
}
