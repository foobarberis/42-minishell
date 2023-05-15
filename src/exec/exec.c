#include "minishell.h"

int exec(t_glb *glob)
{
	size_t       i;
	t_cmd    	*cmd;

	i = 0;
	glob->multiple_cmd = ps_token_list_goto_last(glob->tok)->cmd_index + 1;
	cmd = malloc(sizeof(t_cmd) * glob->multiple_cmd);
	ps_initialisation_cmds(cmd, glob);
	ex_execution(glob, &cmd[i], glob->multiple_cmd);
	i = 0;
	while (i < glob->multiple_cmd)
	{
		// dprintf(2,"je passe ici et lA\n");
		waitpid(cmd[i].pid, NULL, 0);
		i++;
	}
	free_t_cmd(cmd, (int)glob->multiple_cmd);
	return (0);
}
