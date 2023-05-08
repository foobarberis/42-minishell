#include "minishell.h"

/* FIXME: Be careful of return code when using ctrl-c */
/* FIXME: Handle signal in different contexts i.e during exec, during here-doc */
void sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
