#include "minishell.h"

/* https://www.gnu.org/software/bash/manual/html_node/Bourne-Shell-Builtins.html#index-exit */
// https://www.gnu.org/software/bash/manual/html_node/Exit-Status.html

// Exit the shell, returning a status of n to the shell’s parent. If n is
// omitted, the exit status is that of the last command executed. Any trap
// on EXIT is executed before the shell terminates.
int blt_exit(char **argv)
{
	if (!argv)
		return (0);
	if (!argv[1])
		return(rval);
	if (blt_compute_argc(argv) != 2)
		return (f_perror("minishell: exit: too many arguments.\n"), 1);
	rval = f_atoi(argv[1]);
	return (rval);
}
