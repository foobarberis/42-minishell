#include "minishell.h"

static bool contains_valid_option(char *s)
{
	if (f_strlen(s) < 2)
		return (false);
	if ((*s == '-') && (*(s + 1) == 'n'))
	{
		s++;
		while (*s && *s == 'n')
			s++;
	}
	if (!*s)
		return (true);
	return (false);
}

/* https://www.gnu.org/software/bash/manual/html_node/Bash-Builtins.html#index-echo */
/* WARNING: echo -n -n -> prints nothing */
/* WARNING: If argv[i] is not a valid option, subsequent options are printed normally. */
int blt_echo(char **argv)
{
	size_t i;
	bool   newline;

	if (!argv || !argv[1])
		return (0);
	i = 1;
	newline = true;
	while (contains_valid_option(argv[i]))
	{
		newline = false;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i])
			printf(" ");
	}
	if (newline)
		printf("\n");
	return (0);
}

/* int blt_echo(int argc, char **argv)
{
	size_t i;
	bool   newline;

	if (!argv)
		return (0);
	i = 1;
	newline = contains_valid_option(argv[1]);
	if (newline)
		i++;
	while (argc > 0)
	{
		printf("%s", argv[0]);
		argc--;
		argv++;
		if (argc > 0)
			putchar(' ');
	}
	if (newline)
		f_printf("\n");
	return (0);
} */
