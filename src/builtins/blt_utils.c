#include "minishell.h"

size_t blt_compute_argc(char **argv)
{
	size_t i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i])
		i++;
	return (i);
}
