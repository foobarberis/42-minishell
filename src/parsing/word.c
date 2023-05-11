/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:39:39 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/11 10:40:02 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Regroup words between quotes in one string */
void	ps_token_list_group_words(t_glb *glb)
{
	char	*tmp;
	t_token	*curr;
	t_token	*next;

	curr = glb->tok[0];
	while (curr)
	{
		next = curr->next;
		while (next && curr->quote != NONE && (curr->quote == next->quote))
		{
			tmp = f_strjoin(curr->word, next->word);
			if (!tmp)
				panic(glb, CODE_MALLOC);
			free(curr->word);
			curr->word = tmp;
			ps_token_list_node_rm(glb->tok, next);
			next = curr->next;
		}
		curr = curr->next;
	}
}

void	ps_token_list_recreate_words(t_glb *glb)
{
	char	*tmp;
	t_token	*curr;
	t_token	*next;

	curr = glb->tok[0];
	while (curr)
	{
		next = curr->next;
		while (next && (curr->word_index == next->word_index)
			&& (curr->quote == next->quote))
		{
			tmp = f_strjoin(curr->word, next->word);
			if (!tmp)
				panic(glb, CODE_MALLOC);
			free(curr->word);
			curr->word = tmp;
			ps_token_list_node_rm(glb->tok, next);
			next = curr->next;
		}
		curr = curr->next;
	}
}
