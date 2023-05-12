#include "../inc/minishell.h"

int	ps_is_builtin(char *cmd)
{
	if (f_strcmp(cmd, "echo") == 0)
		return (ECHO);
	else if (f_strcmp(cmd, "cd") == 0)
		return (CD);
	else if (f_strcmp(cmd, "pwd") == 0)
		return (PWD);
	else if (f_strcmp(cmd, "export") == 0)
		return (EXPORT);
	else if (f_strcmp(cmd, "unset") == 0)
		return (UNSET);
	else if (f_strcmp(cmd, "env") == 0)
		return (ENV);
	else if (f_strcmp(cmd, "exit") == 0)
		return (EXIT);
	return (NONE);
}
