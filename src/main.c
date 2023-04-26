#include "../inc/minishell.h"
#include "../inc/execution.h"

static int exec(t_glb *glob)
{
	int i;
	int j;
	t_cmd	*cmd;

	i = 0;
	j = 0;
	glob->multiple_cmd = 1;
	cmd = malloc(sizeof(t_cmd) * glob->multiple_cmd);
	initialisation_cmds(cmd, glob);
	single_execution(cmd[0]);
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
		glb->tok = parsing(buf);
		glb->env = env_init((char**)ep);
		if (!glb->tok)
			return (free(glb), EXIT_FAILURE); /* FIXME Add better error handling */
		else
			exec(glb);
		free(buf);
	}
	// FIXME Free everything
	return (EXIT_SUCCESS);
}
