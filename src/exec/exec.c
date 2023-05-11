#include "minishell.h"

/* static int exec(t_glb *glob)
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
} */
