#include "minishell.h"

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
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
		if (!f_isdigit(*s++))
			return (false);
	return (true);
}

static int blt_exit_update_rval(char *path, int argc, char **argv)
{
	return 0;
}

/* FIXME: Make shorter*/
void blt_exit(t_glb *glb, t_cmd *cmd, int argc, char **argv)
{
	char *tmp;
	char *tmp2;
	intmax_t n;

	n = 0;
	g_rval = 0;
	printf("exit\n");
	if (argc > 2)
	{
		g_rval = 1;
		f_dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
	}
	else if (argc == 2)
	{
		n = f_exit_atoi(argv[1]);
		tmp = f_itoa(n);
		tmp2 = argv[1];
		if (*argv[1] == '+')
			tmp2 = argv[1] + 1;
		if (!isnum(argv[1]) || (f_strcmp(tmp2, tmp)))
		{
			g_rval = 2;
			f_dprintf(STDERR_FILENO, "minishell: exit: numeric argument required\n");
		}
		else
			g_rval = (uint8_t)n;
		free(tmp);
	}
	panic(glb, g_rval, cmd);
}
