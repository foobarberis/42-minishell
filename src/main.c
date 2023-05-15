#include "../inc/minishell.h"

static t_glb *msh_init(char **envp)
{
	t_glb *glb;

	glb = malloc(sizeof(t_glb));
	if (!glb)
		panic(glb, CODE_MALLOC);
	glb->tok = malloc(sizeof(t_token *));
	glb->env = malloc(sizeof(t_env *));
	if (!glb->tok || !glb->env)
		panic(glb, CODE_MALLOC);
	glb->tok[0] = NULL;
	glb->env[0] = NULL;
	glb->environ = NULL;
	glb->rl = NULL;
	env_list_from_array(glb, envp);
	env_environ_update(glb);
	return (glb);
}

static void msh_exit(t_glb *glb)
{
	if (!glb)
		return;
	if (glb->rl)
		free(glb->rl);
	if (glb->env)
	{
		env_list_free(glb->env);
		free(glb->env);
	}
	if (glb->tok)
	{
		ps_token_list_free(glb->tok);
		free(glb->tok);
	}
	if (glb->environ)
 		env_environ_free(glb->environ);
	free(glb);
	rl_clear_history();
}

static void reset(t_glb *glb)
{
	ps_token_list_free(glb->tok);
	glb->tok[0] = NULL;
	free(glb->rl);
	glb->rl = NULL;
}

#include <execinfo.h>
void panic(t_glb *glb, int code)
{
	msh_exit(glb);
	if (code == CODE_MALLOC)
		f_perror(ERR_MALLOC);
	exit(code);
}

int g_rval = 0; /* Global variable init */

int main(int ac, char *av[], char *ep[])
{
	(void) ac;
	(void) av;
	t_glb *glb;

	glb = msh_init(ep);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	while (1)
	{
		glb->rl = readline("MSH $ ");
		if (!glb->rl)
			break;
		if (!glb->rl[0])
			continue;
		if (!ps_line_has_balanced_quotes(glb->rl) || glb->rl[0] == '|')
		{
			f_perror(ERR_SYNTAX);
			continue;
		}
		add_history(glb->rl);
		if (ps_token_list_from_array(glb->tok, glb->rl))
			panic(glb, EXIT_FAILURE);
		if (parsing(glb))
		{
			reset(glb);
			continue;
		}
		exec(glb);
		reset(glb);
	}
	msh_exit(glb);
	return (EXIT_SUCCESS);
}
