#include "../inc/minishell.h"

static int exec(t_glb *glob)
{
	size_t       i;
	t_cmd    	*cmd;

	i = 0;
	glob->multiple_cmd = ps_token_list_goto_last(glob->tok)->cmd_index + 1;
	cmd = malloc(sizeof(t_cmd) * glob->multiple_cmd);
	ps_initialisation_cmds(cmd, glob);
	ex_execution(&cmd[i], glob->multiple_cmd);
	i = 0;
	while (i < glob->multiple_cmd)
	{
		if (cmd[i].struct_input[cmd[i].final_input].is_here_doc == 0)
			waitpid(cmd[i].pid, NULL, 0);
		i++;
	}
	free_t_cmd(cmd, (int)glob->multiple_cmd);
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
	glb->env[0] = NULL;
	glb->ep = NULL;
	env_list_from_array(glb->env, envp);
	env_envp_update(glb);
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
	if (glb->ep)
		env_envp_del(glb->ep);
	free(glb);
	rl_clear_history();
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
		ps_token_list_from_array(glb->tok, buf);
		if (!glb->tok)
			continue;
		if (parsing(glb))
		{
			reset(glb, buf);
			continue;
		}
		exec(glb);
		reset(glb, buf);
	}
	msh_exit(glb);
	return (EXIT_SUCCESS);
}
