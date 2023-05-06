static t_glb *msh_init(char **envp)
{
	t_glb *glb;

	glb = malloc(sizeof(t_glb));
	if (!glb)
		return (NULL);
	glb->tok = malloc(sizeof(t_token *));
	if (!glb->tok)
		return (free(glb), NULL);
	glb->env = malloc(sizeof(t_env *));
	if (!glb->env)
		return (free(glb->tok), free(glb), NULL);
	glb->env[0] = NULL;
	glb->ep = NULL;
	env_list_from_array(glb->env, envp);
	env_envp_update(glb);
	glb->tok[0] = NULL;
	return (glb);
}

static void msh_exit(t_glb *glb)
{
	if (!glb)
		return;
	if (glb->env)
	{
		env_list_free_all(glb->env);
		free(glb->env);
	}
	if (glb->ep)
		env_envp_del(glb->ep);
	free(glb);
}

// gcc env.c env_list_utils.c ../mlc/libft.a -I../inc -I../mlc/inc
int main(int ac, char **av, char **ep)
{
	t_glb *glb = msh_init(ep);
	char  *s = f_strdup("HOME=test");
	env_list_key_add(glb, s);
	for (int i = 0; glb->ep[i]; i++)
		printf("%s\n", glb->ep[i]);
	env_list_key_del(glb, s);
	printf("\n\n");
	for (int i = 0; glb->ep[i]; i++)
		printf("%s\n", glb->ep[i]);
	msh_exit(glb);
	free(s);
}
