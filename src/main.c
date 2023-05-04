#include "minishell.h"

// gcc -g3 -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion -fsanitize=undefined,address -lreadline main.c parsing.c env.c ../mlc/libft.a -I../inc -I../mlc/inc

static int exec(t_glb *glb)
{
	return 0;
}

static void cleanup(t_glb *glb)
{
	if (!glb)
		return;
	if (glb->env && glb->env->envp)
	{
		env_array_free(glb->env->envp, glb->env->size);
		free(glb->env);
	}
	if (glb->tok)
		ps_token_list_free_all(glb->tok);
	free(glb);
}

/* FIXME: Be careful of return code when using ctrl-c */
static void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
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
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		buf = readline("MSH $ ");
		if (!buf)
			break;
		if (!*buf)
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
	/* FIXME: Free all */
	if (buf)
		free(buf);
	// cleanup(glb);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
