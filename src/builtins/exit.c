#include "minishell.h"

/* https://www.gnu.org/software/bash/manual/html_node/Bourne-Shell-Builtins.html#index-exit */
// https://www.gnu.org/software/bash/manual/html_node/Exit-Status.html
int blt_exit(char **argv)
{
	if (!argv)
		return (0);
	if (blt_compute_argc(argv) != 2)
		return (f_perror("minishell: exit: too many arguments.\n"), 1);
	rval = f_atoi(argv[1]);
	return (0);
}
