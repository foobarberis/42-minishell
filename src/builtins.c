#include "minishell.h"

/* gcc -Wall -Wextra -g3 -fsanitize=address -lreadline parsing.c env.c builtins.c ../mlc/libft.a -I../inc -I../mlc/inc */

/*
 * Useful links:
 * - https://man7.org/linux/man-pages/man1/cd.1p.html
*/

/* FIXME: Print as in Bash i.e "declare -x key=value" and sort in ASCII order */
void blt_export__array_print(t_env *env)
{
	// duplicate array
	// sort the duplicate
	// print the sorted array and add "declare -x" before each key=value + add "" arround the value
	// free the sorted array
}

// WARNING: When doing "export TEST", TEST does not show up in env but does
// show up in export.

/* TODO: Check if key is */
int blt_export(t_glb *glb, char *key)
{
	if (!env_list_is_valid_id(key))
		return (1);
	if (!key)
		return (env_array_print(glb->env), 0);
	else
		return (env_export(glb->env, key));
}

int blt_unset(t_glb *glb, char *key)
{
	if (!key)
		return (0);
	return (env_unset(glb->env, key));
}

size_t blt_compute_argc(char **argv)
{
	size_t i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i])
		i++;
	return (i);
}

int blt_cd(int argc, char **argv, t_glb *glb)
{
	char *path;

	if (argc > 2)
		return (f_printf("minishell: cd: too many arguments\n"));
	if (!argv[1])
	{
		path = env_extract_value(glb->env, "HOME");
		if (!path || !*path)
			return (f_printf("minishell: cd: HOME not set\n"));
		else
			chdir(path);
	}
	else if (!argv[1][0])
		return (0);
	chdir(argv[1]);
	return (0);
}

#define BUF_SIZE 1024

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;

	char buf[BUF_SIZE];
	t_glb *glb;

	glb = msh_init(envp);
	if (!glb)
		return (EXIT_FAILURE);
	env_unset(glb->env, "HOME");
	printf("cwd :: %s\n", getcwd(buf, BUF_SIZE));
	blt_cd(argc, argv, glb);
	printf("cwd :: %s\n", getcwd(buf, BUF_SIZE));
	env_array_free(glb->env->envp, blt_compute_argc(glb->env->envp));
	free(glb->env);
	free(glb);
	return (0);
}
