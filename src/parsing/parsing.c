/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:35:54 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/08 11:39:18 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * - Turn the readline buffer into a doubly-linked list with one char per
 *   node.
 * - Mark the quote state for each node.
 * - Give the same index for each node which belongs to the same word.
 * - Give the same index for each node which belongs to the same command.
 * - Delete all unquoted spaces.
 * - Look for syntax errors e.g line with a single | or a single pair of
 *   quotes.
 * - Delete unquoted quotes and unquoted pipes.
 *      - WARNING: MS $ '' should produce a node with word member set to
 *        the empty string.
 * - Concatenate nodes with the same word_index into one node (make words
 *   out of individual chars).
 * - Expand variables if necessary.
 * - Turn consecutive nodes with the same quote state into one node.
 * - Fill in type information
 * - Error checking (i.e file exists, program exists, file and folder
 *   permission etc.).
 */

static void token_array_print(t_token **tok)
{
	size_t i;

	printf("%-15s | %-15s | %-15s | %-15s | %-15s\n", "type", "quote", "char *", "word", "cmd");

	printf("-------------------------------------------------------------------"

	       "--------\n");

	i = 0;

	while (tok[i])

	{
		printf("%-15d | %-15d | %-15s | %-15ld | %-15ld\n", tok[i]->type, tok[i]->quote,

		       tok[i]->word, tok[i]->word_index, tok[i]->cmd_index);

		i++;
	}

	f_printf("\n");
}

char	*token_array_to_string(t_token **tok)
{
	int		i;
	char	*tmp;
	char	*new;

	i = 1;
	if (!*tok)
		return (f_strdup(""));
	new = f_strdup(tok[0]->word);
	if (!new)
		return (NULL);
	while (tok[i])
	{
		tmp = f_strjoin(new, tok[i++]->word);
		free(new);
		if (!tmp)
			return (NULL);
		new = tmp;
	}
	return (new);
}

static int	parsing_expand(t_glb *glb)
{
	char	*new;

	parsing_set_index_quote(glb->tok);
	parsing_set_index_word(glb->tok);
	parsing_set_index_cmd(glb->tok);
	if (parsing_expand_variables(glb->tok, glb->env))
		return (f_dprintf(STDERR_FILENO, ERR_MALLOC), 1);
	new = token_array_to_string(glb->tok);
	if (!new)
		panic(glb, CODE_MALLOC, NULL);
	token_array_destroy(glb->tok);
	glb->tok = token_array_create(new);
	free(new);
	if (!glb->tok)
		panic(glb, CODE_MALLOC, NULL);
	return (0);
}

int	parsing(t_glb *glb)
{
	if (parsing_expand(glb))
		return (1);
	parsing_set_index_quote(glb->tok);
	parsing_set_index_word(glb->tok);
	parsing_set_index_cmd(glb->tok);
	parsing_delete_space(glb->tok);
	if (parsing_check_syntax(glb->tok))
		return (1);
	parsing_delete_quote(glb->tok);
	parsing_update_index_word(glb->tok);
	parsing_delete_pipe(glb->tok);
	if (parsing_recreate_words(glb->tok))
		return (f_dprintf(STDERR_FILENO, ERR_MALLOC), 1);
	parsing_fill_type(glb->tok);
	parsing_delete_bracket(glb->tok);
	if (parsing_recreate_strings(glb->tok))
		return (f_dprintf(STDERR_FILENO, ERR_MALLOC), 1);
	glb->old_rval = g_rval;
	g_rval = 0;
	if (parsing_here_doc(glb->tok, glb->env))
		return (f_dprintf(STDERR_FILENO, ERR_MALLOC), 1);
	if (g_rval == 130)
		return (1);
	glb->split = token_split_create(glb->tok);
	if (!glb->split)
		return (f_dprintf(STDERR_FILENO, ERR_MALLOC), 1);
	return (0);
}
