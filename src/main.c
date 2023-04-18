#include "minishell.h"

static int exec(t_glb *glb)
{
	return 0;
}

int main(int argc, char *argv[], char *envp[])
{
	t_glb *glb;
	char  *buf;

	glb = malloc(sizeof(t_glb));
	if (!glb)
		return (EXIT_FAILURE);
	while (1)
	{
		buf = readline("MS $ ");
		if (!buf)
			break;
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
