/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_arr_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:42:15 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/01 09:57:28 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_struct_create(char *word)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->word = f_strdup(word);
	if (!new->word)
		return (free(new), NULL);
	new->type = BASIC;
	new->quote = NONE;
	new->word_index = 0;
	new->cmd_index = 0;
	return (new);
}

t_token	**token_array_create(char *s)
{
	size_t	i;
	char	buf[2];
	t_token	**new;

	i = 0;
	buf[1] = '\0';
	new = f_calloc(f_strlen(s) + 1, sizeof(t_token *));
	if (!new)
		return (NULL);
	while (s[i])
	{
		buf[0] = s[i];
		new[i] = token_struct_create(buf);
		if (!new[i])
			return (token_array_destroy(new), NULL);
		i++;
	}
	return (new);
}

void	token_struct_destroy(t_token *p)
{
	if (!p)
		return ;
	if (p->word)
		free(p->word);
	free(p);
}

void	token_array_destroy(t_token **tok)
{
	size_t	i;

	i = 0;
	while (tok[i])
		token_struct_destroy(tok[i++]);
	free(tok);
}

void	token_array_rm(t_token **tok, size_t pos)
{
	token_struct_destroy(tok[pos]);
	while (tok[pos])
	{
		tok[pos] = tok[pos + 1];
		pos++;
	}
}
