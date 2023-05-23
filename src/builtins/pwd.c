#include "minishell.h"
#include <linux/limits.h>

void blt_pwd(void)
{
	char buf[PATH_MAX];

	g_rval = 0;
	if (!getcwd(buf, PATH_MAX))
	{
		g_rval = 1;
		perror("minishell: pwd: ");
	}
	else
		printf("%s\n", buf);
}
