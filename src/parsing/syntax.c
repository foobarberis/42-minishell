#include "minishell.h"

/* TODO: >| -> parsing error, but |> should not be an error. */

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

/* FIXME: a | a | a | a triggers error */
static bool ps_token_list_is_valid_combination(int a, int b)
{
	if (a == '>' && b == '|')
		return (false);
	else if (a == '<' && b == '|')
		return (false);
	else if (a == '|' && b == '|')
		return (false);
	else if (a == '>' && b == '<')
		return (false);
	else if (a == '<' && b == '>')
		return (false);
	return (true);
}

/* if c < 0 -> next->next is NULL */
static bool ps_token_list_is_syntax_error(int a, int b, int c)
{
	bool comb;

	comb = ps_token_list_is_valid_combination(a, b);
	if (!comb)
		return (true);
	else if (comb && !c)
		return (true);
	else if (comb && ismeta(c))
		return (true);
	return (false);
}

bool ps_token_list_has_syntax_error(t_token **tok)
{
	int      c;
	t_token *next;
	t_token *curr;

	if (!tok || !*tok)
		return (false);
	curr = *tok;
	if (curr->word[0] == '|')
		return (f_perror(ERR_SYNTAX), true);
	while (curr)
	{
		next = curr->next;
		if (ismeta(curr->word[0]) && curr->quote == NONE)
		{
			if (!next)
				return (f_perror(ERR_SYNTAX), true);
			if (next->next)
				c = next->next->word[0];
			else
				c = 0;
			if (ps_token_list_is_syntax_error(curr->word[0], next->word[0], c))
				return (true);
		}
		curr = next;
	}
	return (false);
}
