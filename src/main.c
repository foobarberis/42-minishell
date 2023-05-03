#include "minishell.h"

// gcc -g3 -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion -fsanitize=undefined,address -lreadline main.c parsing.c env.c ../mlc/libft.a -I../inc -I../mlc/inc

static int exec(t_glb *glb)
{
	return 0;
}

int main(int ac, char *av[], char *ep[])
{
	(void) ac;
	(void) av;
	t_glb *glb;
	char  *buf;

	glb = init_glb(ep);
	if (!glb)
		return (EXIT_FAILURE);
	while (1)
	{
		buf = readline("MSH $ ");
		if (!buf || !*buf)
			continue;
		if (!ps_line_has_balanced_quotes(buf))
		{
			f_perror(SYNTAX);
			continue;
		}
		else
		{
			add_history(buf);
			glb->tok = ps_token_list_from_array(buf);
			if (!glb->tok)
				continue;
		}
		if (!parsing(glb))
			exec(glb);
		if (glb->tok)
			ps_token_list_free_all(glb->tok);
		free(buf);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
