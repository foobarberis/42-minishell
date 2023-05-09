#include "minishell.h"

static bool contains_valid_option(char *s)
{
	return (true);
}

/* https://www.gnu.org/software/bash/manual/html_node/Bash-Builtins.html#index-echo */
/* WARNING: echo -n -n -> prints nothing */
/* WARNING: If argv[i] is not a valid option, subsequent options are printed normally. */
int blt_echo(char **argv)
{
	size_t i;
	bool newline;

	if (!argv)
		return (0);
	i = 1;
	newline = contains_valid_option(argv[1]);
	if (newline)
		i++;
	while (argv[i])
		if (!contains_valid_option(argv[i]))
			f_printf("%s", argv[i++]);
	if (newline)
		f_printf("\n");
	return (0);
}
