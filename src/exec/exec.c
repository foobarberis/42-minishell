#include "minishell.h"

int	exec(t_glb *glob)
{
	int status;
	int	i;
	t_cmd	*cmd;

	i = 0;
	glob->multiple_cmd = (int)ps_token_list_goto_last(glob->tok)->cmd_index + 1;
	cmd = malloc(sizeof(t_cmd) * glob->multiple_cmd);
	ps_initialisation_cmds(cmd, glob);
	ex_execution(glob, &cmd[i], glob->multiple_cmd);
	i = 0;
	while (i < glob->multiple_cmd)
	{
		waitpid(cmd[i].pid, &status, 0);
		if (WIFEXITED(status))
			g_rval = WEXITSTATUS(status);
		i++;
	}
	close_fd(cmd, glob->multiple_cmd);
	free_t_cmd(cmd, glob->multiple_cmd);
	return (0);
}
