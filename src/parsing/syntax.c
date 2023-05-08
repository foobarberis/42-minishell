#include "minishell.h"

bool ps_line_has_balanced_quotes(char *s)
{
	size_t nsimple;
	size_t ndouble;

	nsimple = 0;
	ndouble = 0;
	while (*s)
	{
		if (*s == '"')
			ndouble++;
		else if (*s == '\'')
			nsimple++;
		s++;
	}
	if (nsimple % 2 || ndouble % 2)
		return (false);
	return (true);
}

static int check_further(int a, int b)
{
	if ((a == '>' && b == '>') || (a == '<' && b == '<'))
		return (1);
	if ((a == '|' && b == '<') || (a == '|' && b == '>'))
		return (2);
	return (0);
}

static int check_syntax(t_token **tok)
{
	t_token *next;
	t_token *curr;

	curr = *tok;
	while (curr)
	{
		next = curr->next;
		if (ismeta(curr->word[0]) && curr->quote == NONE)
		{
			if (next && (check_further(curr->word[0], next->word[0]) == 1))
				next = next->next;
			if (next && (check_further(curr->word[0], next->word[0]) == 2))
			{
				next = next->next;
				if (next && (curr->next->word[0] == next->word[0]))
					next = next->next;
			}
			if (!next || ismeta(next->word[0]))
				return (1);
		}
		curr = next;
	}
	return (0);
}

bool ps_token_list_has_syntax_error(t_token **tok)
{
	if (!tok || !*tok)
		return (false);
	if (check_syntax(tok))
		return (true);
	return (false);
}
