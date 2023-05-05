#include "minishell.h"

// gcc -g3 -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion -fsanitize=undefined,address -lreadline main.c parsing.c env.c ../mlc/libft.a -I../inc -I../mlc/inc

static int exec(t_glb *glb)
{
	return 0;
}

static t_glb *msh_init(char **envp)
{
	t_glb *glb;

	glb = malloc(sizeof(t_glb));
	if (!glb)
		return (NULL);
	glb->tok = malloc(sizeof(t_token *));
	if (!glb->tok)
		return (free(glb), NULL);
	glb->env = malloc(sizeof(t_env *));
	if (!glb->env)
		return (free(glb->tok), free(glb), NULL);
	glb->env[0] = NULL;
	env_list_from_array(glb->env, envp);
	glb->tok[0] = NULL;
	return (glb);
}

static void msh_exit(t_glb *glb)
{
	if (!glb)
		return;
	if (glb->env)
	{
		env_list_free_all(glb->env);
		free(glb->env);
	}
	if (glb->tok)
	{
		ps_token_list_free_all(glb->tok);
		free(glb->tok);
	}
	free(glb);
	rl_clear_history();
}

int main(int ac, char *av[], char *ep[])
{
	(void) ac;
	(void) av;
	t_glb *glb;
	char  *buf;

	glb = msh_init(ep);
	if (!glb)
		return (EXIT_FAILURE);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	while (1)
	{
		buf = readline("MSH $ ");
		if (!buf)
			break;
		if (!*buf)
			continue;
		if (!ps_line_has_balanced_quotes(buf))
		{
			f_perror(ERR_SYNTAX);
			continue;
		}
		else
		{
			add_history(buf);
			ps_token_list_from_array(glb->tok, buf);
			if (!glb->tok)
				continue;
		}
		if (parsing(glb))
		{
			f_perror(ERR_PARSING);
			continue;
		}
		exec(glb);
		ps_token_list_free_all(glb->tok);
		glb->tok[0] = NULL;
		free(buf);
	}
	msh_exit(glb);
	return (EXIT_SUCCESS);
}
