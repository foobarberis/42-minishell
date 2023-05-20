
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:35:54 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/15 12:30:29 by mbarberi         ###   ########.fr       */
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
		printf("%-15d | %-15d | %-15s | %-15ld | %-15ld\n", tok[i]->type, tok[i]->quote, tok[i]->word, tok[i]->word_index, tok[i]->cmd_index);
		i++;
	}
	f_printf("\n");
}

int	parsing(t_glb *glb)
{
	parsing_set_index_quote(glb->tok);
	parsing_set_index_word(glb->tok);
	parsing_set_index_cmd(glb->tok);
	parsing_delete_space(glb->tok);
	parsing_delete_quote(glb->tok);
	if (parsing_check_syntax(glb->tok))
		return (1);
	parsing_update_index_word(glb->tok);
	parsing_delete_pipe(glb->tok);
	if (parsing_expand_variables(glb->tok, glb->env))
		return (f_dprintf(STDERR_FILENO, ERR_MALLOC), 1);
	if (parsing_recreate_words(glb->tok))
		return (f_dprintf(STDERR_FILENO, ERR_MALLOC), 1);
	parsing_fill_type(glb->tok);
	parsing_delete_bracket(glb->tok);
	token_array_print(glb->tok);
	return (0);
}
