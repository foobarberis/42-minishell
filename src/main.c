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
	while (i < glob->multiple_cmd)
	{
		j = 0;
		print_double_array(cmd[i].args, "array of cmd");
		printf("Path cmd = %s\n", cmd[i].path_cmd);
		while (cmd[i].struct_input && j < cmd[i].struct_input->fd_input)
		{
			printf("input file = %s\n", cmd[i].struct_input[j].input);
			j++;
		}
		j = 0;
		while (cmd[i].struct_output && j < cmd[i].struct_output->fd_output)
		{
			printf("output files = %s\n", cmd[i].struct_output[j].output);

			j++;
		}
		printf("\n");
		i++;
	}
//	single_execution(cmd[0]);
	return (0);
}

int main(const int ac, const char *av[], const char *ep[])
{
	t_glb *glb;
	char  *buf;

	(void)ac;
	(void)av;
	(void)ep;
	glb = malloc(sizeof(t_glb));
	if (!glb)
		return (EXIT_FAILURE);
	while (1)
	{
		buf = readline("MS $ ");
		if (!buf || !*buf)
			continue;
		glb->tok = parsing(buf);
		if (!glb->tok)
			return (free(glb), EXIT_FAILURE); /* FIXME Add better error handling */
		else
			exec(glb);
		free(buf);
	}
	// FIXME Free everything
	return (EXIT_SUCCESS);
}
