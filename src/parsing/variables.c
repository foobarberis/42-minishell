/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:38:50 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/16 16:48:47 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_legal(int c)
{
	return (f_isalnum(c) || c == '_' || c == '?' || c == 0);
}

static int	recreate_variables_cond(t_token *curr, t_token *next)
{
	if (!curr || !next)
		return (0);
	return (curr->word && curr->word[0] == '$'
		&& is_legal(next->word[0])
		&& (curr->word_index == next->word_index)
		&& (curr->quote == next->quote));
}

void	ps_token_list_recreate_variables(t_glb *glb)
{
	char	*tmp;
	t_token	*curr;
	t_token	*next;

	curr = glb->tok[0];
	while (curr)
	{
		next = curr->next;
		while (recreate_variables_cond(curr, next))
		{
			tmp = f_strjoin(curr->word, next->word);
			if (!tmp)
				panic(glb, CODE_MALLOC);
			free(curr->word);
			curr->word = tmp;
			ps_token_list_node_rm(glb->tok, next);
			next = curr->next;
			if (curr->word && curr->word[0] == '$'
				&& (curr->word[1] == '?' || curr->word[1] == 0))
				break ;
		}
		curr = next;
	}
}

/* FIXME: Secure this */
void	ps_token_list_expand_variables(t_glb *glb)
{
	char	*value;
	t_token	*curr;

	curr = glb->tok[0];
	while (curr)
	{
		if (curr->word[0] == '$' && curr->word[1] && curr->quote != SIMPLE)
		{
			if (curr->word[1] == '?')
			{
				value = f_itoa(g_rval);
				g_rval = 0; // FIXME: Maybe move this some place else
			}
			else
				value = env_getenv(glb->env, &curr->word[1]);
			if (!value)
				panic(glb, CODE_MALLOC);

			curr->word = f_strdup(value);
		}
		curr = curr->next;
	}
}
