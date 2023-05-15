#include "minishell.h"

/* https://man7.org/linux/man-pages/man1/cd.1p.html */
int blt_cd(int argc, char **argv, t_glb *glb)
{
	char *path;

	if (argc > 2)
		return (f_dprintf(STDERR_FILENO, "minishell: cd: too many arguments\n"));
	if (!argv[1])
	{
		path = env_getenv(glb->env, "HOME");
		if (!path || !*path)
			return (f_dprintf(STDERR_FILENO, "minishell: cd: HOME not set\n"));
		else
			chdir(path);
	}
	else if (!argv[1][0])
		return (0);
	chdir(argv[1]);
	return (0);
}
