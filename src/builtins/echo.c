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
