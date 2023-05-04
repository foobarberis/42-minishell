#include "../inc/minishell.h"
#include "../inc/execution.h"

int find_nb_cmd(t_token *tok);
t_token	**split_tok_into_cmd(t_token *tok, size_t nb_cmd);
void	end_tok_lst(t_token *tok, size_t i);

static int exec(t_glb *glob)
{
	int i;
	t_cmd	*cmd;
	t_token **final_tok_lst;

	i = 0;
	glob->multiple_cmd = find_nb_cmd(glob->tok[0]);
	final_tok_lst = split_tok_into_cmd(glob->tok[0], glob->multiple_cmd);
	glob->tok = final_tok_lst;
	cmd = malloc(sizeof(t_cmd) * glob->multiple_cmd);
	ps_initialisation_cmds(cmd, glob);
	ex_execution(&cmd[i], glob->multiple_cmd);
	i = 0;
	while (i < glob->multiple_cmd)
	{
		waitpid(cmd[i].pid, NULL, 0);
		i++;
	}
	ps_token_list_free_all(final_tok_lst);
	free_t_cmd(cmd, glob->multiple_cmd);
	return (0);
}

int main(const int ac, const char *av[], const char *ep[])
{
	t_glb *glb;
	char  *buf;

	(void)ac;
	(void)av;
	glb = malloc(sizeof(t_glb));
	if (!glb)
		return (EXIT_FAILURE);
	while (1)
	{
		buf = readline("MS $ ");
		if (!buf || !*buf)
			continue;
		add_history(buf);
		glb->tok = parsing(buf);
		glb->env = env_init((char**)ep);
		if (!glb->tok)
			return (free(glb), EXIT_FAILURE); /* FIXME Add better error handling */
		else
		{
			exec(glb);
		}
		free(buf);
	}
	// FIXME Free everything
	return (EXIT_SUCCESS);
}


int find_nb_cmd(t_token *tok)
{
	int nb;

	nb = 0;
	while (tok)
	{
		nb = (int)tok->cmd_index;
		tok = tok->next;
	}
	return (nb + 1);
}

t_token	**split_tok_into_cmd(t_token *tok, size_t nb_cmd)
{
	size_t	i;
	t_token **final_tok_lst;

	i = 0;
	final_tok_lst = malloc(sizeof(t_token *) * nb_cmd);
	while(tok)
	{
		final_tok_lst[i] = tok;
		while(tok && tok->cmd_index == i)
			tok = tok->next;
		end_tok_lst(final_tok_lst[i], i + 1);
		i++;
	}
	return (final_tok_lst);
}

void	end_tok_lst(t_token *tok, size_t i)
{
	while (tok && tok->cmd_index < i)
		tok = tok->next;
	if (tok)
		tok->prev->next = NULL;
}