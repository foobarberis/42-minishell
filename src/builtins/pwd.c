#include "minishell.h"
#include <linux/limits.h>

int blt_pwd(void)
{
	char buf[PATH_MAX];

	if (!getcwd(buf, PATH_MAX))
		return (perror("minishell: cwd: "), 1);
	printf("%s\n", buf);
	return (0);
}
