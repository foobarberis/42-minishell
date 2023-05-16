#include "minishell.h"

/* https://www.gnu.org/software/bash/manual/html_node/Bourne-Shell-Builtins.html#index-exit */
/* https://www.gnu.org/software/bash/manual/html_node/Exit-Status.html */

// Exit the shell, returning a status of n to the shell’s parent. If n is
// omitted, the exit status is that of the last command executed. Any trap
// on EXIT is executed before the shell terminates.

// 9223372036854775807
// -9223372036854775809
static intmax_t	f_exit_atoi(const char *s)
{
	intmax_t	x;
	intmax_t	sign;

	x = 0;
	sign = 1;
	while (f_isspace(*s))
		s++;
	if (*s == '-')
		sign *= -1;
	if (*s == '-' || *s == '+')
		s++;
	while (f_isdigit(*s))
		x = x * 10 + *s++ - '0';
	return (x * sign);
}

static bool isnum(char *s)
{
	if (!s || !*s)
		return (false);
	if (*s == '-')
		s++;
	while (*s)
	{
		if (!f_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}


int blt_exit(t_glb *glb, int argc, char **argv)
{
	char *tmp;
	intmax_t n;

	n = 0;
	if (argc > 2)
		return (g_rval = 1, f_dprintf(STDERR_FILENO, "exit\nminishell: exit: too many arguments.\n"), 1);
	else if (!argv[1])
		g_rval = 0;
	else
	{
		n = f_exit_atoi(argv[1]);
		tmp = f_itoa(n);
		if (!isnum(argv[1]) || (f_strcmp(argv[1], tmp) != 0))
			return (free(tmp), g_rval = 2, f_dprintf(STDERR_FILENO, "exit\nminishell: exit: numeric argument required.\n"), 1);
		g_rval = (int)f_abs(n % 255);
		free(tmp);
	}
	printf("exit\n");
	return (0);
}
