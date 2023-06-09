/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:16:05 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/09 10:44:06 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (parsing_expand_variables(tok, env))
		return (f_dprintf(STDERR_FILENO, ERR_MALLOC),
			token_array_destroy(tok), NULL);
	s = token_array_to_string(tok);
	if (!s)
		return (NULL);
	token_array_destroy(tok);
	return (s);
}
