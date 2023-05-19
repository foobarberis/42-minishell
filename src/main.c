#include "../inc/minishell.h"

static t_glb *msh_init(char **envp)
{
	t_glb *glb;

	glb = malloc(sizeof(t_glb));
	if (!glb)
		panic(glb, CODE_MALLOC, NULL);
	glb->tok = malloc(sizeof(t_token *));
	glb->tok[0] = NULL;
	glb->rl = NULL;
	glb->env = env_init(envp);
	if (!glb->tok || !glb->env)
		panic(glb, CODE_MALLOC, NULL);
	return (glb);
}

static void msh_exit(t_glb *glb)
{
	if (!glb)
		return;
	if (glb->rl)
		free(glb->rl);
	if (glb->tok)
	{
		ps_token_list_free(glb->tok);
		free(glb->tok);
	}
	if (glb->env)
 		env_array_destroy(glb->env, env_array_get_size(glb->env));
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

void panic(t_glb *glb, int code, t_cmd *cmd)
{
	close_fd(cmd, glb->multiple_cmd);
	free_t_cmd(cmd, cmd->glb->multiple_cmd);
	msh_exit(glb);
	if (code == CODE_MALLOC)
		f_dprintf(STDERR_FILENO, ERR_MALLOC);
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
	while (glb)
	{
		glb->rl = readline("MSH $ ");
		if (!glb->rl)
			break;
		if (!glb->rl[0])
			continue;
		add_history(glb->rl);
		if (ps_token_list_from_array(glb->tok, glb->rl))
			panic(glb, EXIT_FAILURE, NULL);
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
