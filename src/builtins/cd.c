#include "minishell.h"
#include <linux/limits.h>

static int update_pwd(t_glb *glb)
{
	char *tmp;
	char *pwd;
	char buf[PATH_MAX];

	tmp = env_getenv(glb->env, "PWD");
	printf("DEBUG tmp :: %s\n", tmp);
	pwd = f_strjoin("OLDPWD=", tmp);
	printf("DEBUG :: %s\n", pwd);
	env_list_key_add(glb, pwd);
	free(tmp);
	free(pwd);
	pwd = f_strjoin("PWD=", getcwd(buf, PATH_MAX));
	printf("DEBUG :: %s\n", pwd);
	env_list_key_add(glb, pwd);
	free(pwd);
	return (0);
}

/* https://man7.org/linux/man-pages/man1/cd.1p.html */
int blt_cd(t_glb *glb, int argc, char **argv)
{
	int   ret;
	char *path;

	if (argc > 2)
		return (f_dprintf(STDERR_FILENO, "minishell: cd: too many "
		                                 "arguments\n"));
	if (!argv[1])
	{
		path = env_getenv(glb->env, "HOME");
		if (!path || !*path)
			return (f_dprintf(STDERR_FILENO, "minishell: cd: HOME not set\n"));
		ret = chdir(path);
		if (ret)
			return (perror("minishell: cd: "), 1);
	}
	else if (!argv[1][0])
		return (0);
	ret = chdir(argv[1]);
	if (ret)
		return (perror("minishell: cd: "), 1);
	update_pwd(glb);
	return (0);
}
