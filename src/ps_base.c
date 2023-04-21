#include "minishell.h"
/* gcc -Wall -Wextra -lreadline -g3 -fsanitize=address ps_token.c ps_base.c ps_token_list_utils.c ../mlc/libft.a -I../inc -I../mlc/inc */

static bool ps_line_has_balanced_quotes(char *s)
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

int main(const int ac, const char *av[], const char *ep[])
{
	(void) ac;
	(void) av;
	(void) ep;
	t_token *tok;
	char    *buf;

	while (1)
	{
		buf = readline("MS $ ");
		if (!buf || !*buf)
			continue;
		if (!ps_line_has_balanced_quotes(buf))
			printf("minishell: syntax error.\n");
		else
		{
			tok = ps_token_list_from_array(buf);
			if (!tok)
				break;
			ps_token_list_mark_quotes(tok);
			ps_token_list_print(tok);
			ps_token_list_free_all(tok);
		}
		free(buf);
	}
	return (EXIT_SUCCESS);
}
