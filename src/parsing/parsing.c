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

static int ps_token_list_parse(t_glb *glb)
{
	ps_token_list_set_index_quote(glb->tok);
	ps_token_list_set_index_word(glb->tok);
	ps_token_list_set_index_cmd(glb->tok);
	ps_token_list_delete_quote(glb->tok);
	ps_token_list_delete_space(glb->tok);
	if (ps_token_list_has_syntax_error(glb->tok))
	  	return (f_perror(ERR_SYNTAX), 1);
	ps_token_list_update_index_word(glb->tok);
	ps_token_list_delete_pipe(glb->tok);
	ps_token_list_recreate_variables(glb->tok);
	ps_token_list_expand_variables(glb->tok, glb->env);
	ps_token_list_recreate_words(glb->tok);
	ps_token_list_fill_type(glb->tok);
	ps_token_list_delete_dollar(glb->tok);
	ps_token_list_delete_bracket(glb->tok);
	ps_token_list_group_words(glb->tok);
//	ps_token_list_print(glb->tok);
	return (0);
}

int parsing(t_glb *glb)
{
	if (!glb || !glb->tok || !glb->env)
		return (0);
	if (ps_token_list_parse(glb))
		return (1);
	return (0);
}
