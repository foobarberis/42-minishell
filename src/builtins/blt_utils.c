#include "minishell.h"

int blt_compute_argc(char **argv)
{
	int i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i])
		i++;
	return (i);
}
