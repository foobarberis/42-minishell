/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:16:05 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/13 08:45:02 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	here_doc__expand_variables(t_token **tok, char **env)
{
	size_t	i;
	char	*value;

	i = 0;
	if (parsing_recreate_variables(tok))
		return (1);
	while (tok[i])
	{
		if (*tok[i]->word == '$' && tok[i]->word[1])
		{
			value = get_value(env, &tok[i]->word[1], tok[i]->quote);
			if (!value)
				return (1);
			if (!*value)
			{
				token_array_rm(tok, i);
				free(value);
				continue ;
			}
			free(tok[i]->word);
			tok[i]->word = value;
		}
		i++;
	}
	return (0);
}

char	*here_doc_expand_variables(char **env, char *buf)
{
	char	*s;
	t_token	**tok;

	if (!*buf)
		return (buf);
	tok = token_array_create(buf);
	free(buf);
	if (!tok)
		return (NULL);
	parsing_set_index_quote(tok);
	parsing_set_index_word(tok);
	if (here_doc__expand_variables(tok, env))
		return (f_dprintf(STDERR_FILENO, ERR_MALLOC),
			token_array_destroy(tok), NULL);
	s = token_array_to_string(tok);
	if (!s)
		return (NULL);
	token_array_destroy(tok);
	return (s);
}
