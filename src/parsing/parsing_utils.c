#include "minishell.h"

static size_t f_ndigit(intmax_t n, int baselen)
{
	size_t l;

	l = 0;
	if (n <= 0)
		l += 1;
	while (n)
	{
		l++;
		n /= baselen;
	}
	return (l);
}

char *f_itoa(intmax_t n)
{
	size_t    l;
	uintmax_t nb;
	char     *s;

	l = f_ndigit(n, 10);
	s = malloc(l + 1);
	if (!s)
		return (NULL);
	s[l] = '\0';
	if (n < 0)
		s[0] = '-';
	else if (!n)
		s[0] = '0';
	nb = f_abs(n);
	while (nb)
	{
		s[--l] = (char)(nb % 10 + '0');
		nb /= 10;
	}
	return (s);
}

int ismeta(int c)
{
	return (c == '<' || c == '>' || c == '|');
}

/**
 * @brief Check if the character is legal in the context of Linux filename.
 * A Linux file's name can contain any bytes which are not NUL (0x00) or '\'
 * (0x5C).
 * @param c The character to test.
 * @return
 */
int islegal(int c)
{
	return (!ismeta(c) && isprint(c) && c != '"' && c != '\''); /* FIXME: Replace with f_isprint */
}

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

void ps_token_list_print(t_token **tok)
{
	t_token *curr;

	curr = *tok;
	printf("%-15s | %-15s | %-15s | %-15s | %-15s\n", "type", "quote", "char *", "word", "cmd");
	printf("-------------------------------------------------------------------"
	       "--------\n");
	while (curr)
	{
		if (curr->word)
		{
			if (curr->word[0])
				printf("%-15d | %-15d | %-15s | %-15ld | %-15ld\n", curr->type, curr->quote, curr->word, curr->word_index, curr->cmd_index);
			else
				printf("%-15d | %-15d | %-15s | %-15ld | %-15ld\n", curr->type, curr->quote, "(empty)", curr->word_index, curr->cmd_index);
		}
		curr = curr->next;
	}
	f_printf("\n");
}
