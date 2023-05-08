#include "minishell.h"

void ps_token_list_from_array(t_token **tok, char *s)
{
	char buf[2];

	if (!tok || !s)
		return;
	buf[1] = '\0';
	while (*s)
	{
		buf[0] = *s++;
		ps_token_list_node_add(tok, ps_token_list_node_create(buf));
	}
}

ps_token_list_print(t_token **tok)
{
	t_token *curr;

	curr = *tok;
	printf("%-15s | %-15s | %-15s | %-15s | %-15s\n", "type", "quote", "char *", "word", "cmd");
	printf("-------------------------------------------------------------------"
	       "--------\n");
	while (curr)
	{
		if (curr->word)
			printf("%-15d | %-15d | %-15s | %-15ld | %-15ld\n", curr->type, curr->quote, curr->word, curr->word_index, curr->cmd_index);
		curr = curr->next;
	}
	f_printf("\n");
}

/* FIXME: */
bool ismeta(int c)
{
	// return (c == '<' || c == '>' || c == '|' || c == ' ' || c == '\t' || c == '\n');
	return (c == '<' || c == '>' || c == '|');
}

/* FIXME: Replace isprint with f_isprint */
int is_legal_var_char(int c)
{
	return (!ismeta(c) && isprint(c));
}
