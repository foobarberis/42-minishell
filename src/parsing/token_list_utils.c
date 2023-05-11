/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:36:21 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/11 10:38:29 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ps_token_list_node_create(char *s)
{
	t_token	*new;

	if (!s)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->word = f_strdup(s);
	if (!new->word)
		return (free(new), NULL);
	new->type = BASIC;
	new->quote = NONE;
	new->word_index = 0;
	new->cmd_index = 0;
	new->next = NULL;
	return (new);
}

void	ps_token_list_node_destroy(t_token *node)
{
	if (!node)
		return ;
	if (node->word)
		free(node->word);
	free(node);
}

void	ps_token_list_node_add(t_token **tok, t_token *node)
{
	t_token	*last;

	if (!*tok)
		*tok = node;
	else
	{
		last = ps_token_list_goto_last(tok);
		if (last)
			last->next = node;
	}
}

void	ps_token_list_node_rm(t_token **tok, t_token *node)
{
	t_token	*curr;
	t_token	*next;

	curr = *tok;
	if (curr == node)
	{
		*tok = curr->next;
		return (ps_token_list_node_destroy(curr));
	}
	while (curr)
	{
		next = curr->next;
		if (next == node)
		{
			curr->next = next->next;
			return (ps_token_list_node_destroy(next));
		}
		curr = next;
	}
}

t_token	*ps_token_list_goto_last(t_token **tok)
{
	t_token	*curr;

	curr = *tok;
	while (curr)
	{
		if (!curr->next)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
