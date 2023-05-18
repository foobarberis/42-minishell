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
	while (1)
	{
		glb->rl = readline("MSH $ ");
		if (!glb->rl)
			break;
		if (!glb->rl[0])
			continue;
		if (!ps_line_has_balanced_quotes(glb->rl) || glb->rl[0] == '|')
		{
			f_dprintf(STDERR_FILENO, ERR_SYNTAX);
			continue;
		}
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

static char *here_doc_loop(char *here_doc, char *rl, char *tmp, char *lim)
{
	while (1)
	{
		free(rl);
		rl = readline("> ");
		if (!rl)
		{
			f_dprintf(STDERR_FILENO, "minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", lim);
			break;
		}
		if (!f_strcmp(rl, lim))
		{
			free(rl);
			break;
		}
		tmp = f_strjoin(here_doc, rl);
		if (!tmp)
			return (free(here_doc), free(rl), NULL);
		free(here_doc);
		here_doc = tmp;
	}
	return (here_doc);
}

static char *my_here_doc(char *lim)
{
	char *s;
	char **buf;

	buf = f_calloc(3, sizeof(char *));
	if (!buf)
		return (NULL);
	s = here_doc_loop(buf[0], buf[1], buf[2], lim);
	free(buf);
	return (s);
}

int main(void)
{
	char *here_doc;

	here_doc = my_here_doc("EOF");
	printf("%s\n", here_doc);
	free(here_doc);
}

/* static char *here_doc_loop(char *here_doc, char *rl, char *tmp, char *lim)
{
	if (!here_doc || !rl || !tmp)
	while (1)
	{
		free(rl);
		rl = readline("> ");
		if (!rl)
		{
			f_dprintf(STDERR_FILENO, "minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", lim);
			break;
		}
		if (!f_strcmp(rl, lim))
		{
			free(rl);
			break;
		}
		tmp = f_strjoin(here_doc, rl);
		if (!tmp)
			return (free(here_doc), free(rl), NULL);
		free(here_doc);
		here_doc = tmp;
	}
	return (here_doc);
}

static char *my_here_doc(char *lim)
{
	char *buf[3]
	return (here_doc_loop(f_calloc(1, sizeof(char *)), f_calloc(1, sizeof(char *)), f_calloc(1, sizeof(char *)), lim));
} */
