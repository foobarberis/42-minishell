#include "execution.h"
#include "minishell.h"

void	exec_builtin(int builtin, char **arg)
{
	if (builtin == ECHO)
		ex_echo(arg);
	else if (builtin == CD)
		ex_cd(arg);
	else if (builtin == PWD)
		ex_pwd();
	else if (builtin == EXPORT)
		ex_export(arg);
	else if (builtin == UNSET)
		ex_unset(arg);
	else if (builtin == ENV)
		ex_env();
	else if (builtin == EXIT)
		ex_exit();
}