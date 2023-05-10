#include "../inc/minishell.h"

int       find_nb_cmd(t_token *tok);
t_token **split_tok_into_cmd(t_token *tok, size_t nb_cmd);
void      end_tok_lst(t_token *tok, size_t i);
void      free_lst_tok(t_token **tok, int nb_cmd);

static int exec(t_glb *glob)
{
	int       i;
	t_cmd    *cmd;
	t_token **final_tok_lst;

	i = 0;
	glob->multiple_cmd = find_nb_cmd(glob->tok[0]);
	final_tok_lst = split_tok_into_cmd(glob->tok[0], glob->multiple_cmd);
	cmd = malloc(sizeof(t_cmd) * glob->multiple_cmd);
	ps_initialisation_cmds(cmd, glob, final_tok_lst);
	ex_execution(&cmd[i], glob->multiple_cmd);
	i = 0;
	while (i < glob->multiple_cmd)
	{
		waitpid(cmd[i].pid, NULL, 0);
		i++;
	}
	free_t_cmd(cmd, glob->multiple_cmd);
	return (0);
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
	glb->tok[0] = NULL;
	glb->env[0] = NULL;
	glb->ep = NULL;
	env_list_from_array(glb->env, envp);
	env_envp_update(glb);
	return (glb);
}

static void msh_exit(t_glb *glb, char *buf)
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
	if (glb->ep)
		env_envp_del(glb->ep);
	free(glb);
	rl_clear_history();
	if (buf)
		free(buf);
}

static void reset(t_glb *glb, char *buf)
{
	ps_token_list_free_all(glb->tok);
	glb->tok[0] = NULL;
	free(buf);
}

int rval = 0; /* Global variable init */
int main(int ac, char *av[], char *ep[])
{
	(void) ac;
	(void) av;
	t_glb *glb;
	char  *buf;
	int    pars;

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
		if (!ps_line_has_balanced_quotes(buf) || buf[0] == '|')
		{
			f_perror(ERR_SYNTAX);
			continue;
		}
		add_history(buf);
		if (ps_token_list_from_array(glb->tok, buf))
			break;
		if (!glb->tok) /* WRONG */
			continue;
		pars = parsing(glb);
		if (pars == 1)
		{
			reset(glb, buf);
			continue;
		}
		else if (pars == 2)
			break;
		// exec(glb);
		reset(glb, buf);
	}
	msh_exit(glb, buf);
	return (EXIT_SUCCESS);
}

int find_nb_cmd(t_token *tok)
{
	int nb;

	nb = 0;
	while (tok)
	{
		nb = (int) tok->cmd_index;
		tok = tok->next;
	}
	return (nb + 1);
}

void end_tok_lst(t_token *tok, size_t i)
{
	while (tok->next && tok->next->cmd_index < i)
		tok = tok->next;
	tok->next = NULL;
}

t_token **split_tok_into_cmd(t_token *tok, size_t nb_cmd)
{
	size_t    i;
	t_token **final_tok_lst;

	i = 0;
	final_tok_lst = malloc(sizeof(t_token *) * nb_cmd); /* WARNING: Leaks */
	while (tok)
	{
		final_tok_lst[i] = tok;
		while (tok->next && tok->next->cmd_index == i)
			tok = tok->next;
		tok = tok->next;
		i++;
	}
	i = 0;
	while (i < nb_cmd - 1)
	{
		end_tok_lst(final_tok_lst[i], i + 1);
		i++;
	}
	return (final_tok_lst);
}
