#include "minishell.h"

static void update_pwd(t_glb *glb)
{
	char *tmp;
	char buf[PATH_MAX];

	tmp = env_getenv(glb->env, "PWD");
	glb->env = env_key_add(glb->env, f_strjoin("OLDPWD=", tmp));
	if (!glb->env)
		panic(glb, CODE_MALLOC, NULL);
	glb->env = env_key_add(glb->env, f_strjoin("PWD=", getcwd(buf, PATH_MAX)));
	if (!glb->env)
		panic(glb, CODE_MALLOC, NULL);
}

int blt_cd(t_glb *glb, int argc, char **argv)
{
	char *path;

	g_rval = 0;
	if (argc > 2)
	{
		g_rval = 1;
		f_dprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
	}
	else if (!argv[1])
	{
		path = env_getenv(glb->env, "HOME");
		if (!path || !*path)
			return (f_dprintf(STDERR_FILENO, "minishell: cd: HOME not set\n"));
		if (chdir(path))
			return (perror("minishell: cd: "), 1);
	}
	else if (!argv[1][0])
		return (0);
	else if (chdir(argv[1]))
		return (f_dprintf(STDERR_FILENO, "minishell: cd: %s: ", argv[1]), perror(""), 1);
	update_pwd(glb);
	return (0);
}
