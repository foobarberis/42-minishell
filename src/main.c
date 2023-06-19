/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:54:05 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/19 16:11:43 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_glb	*msh_init(char **envp)
{
	t_glb	*glb;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	glb = malloc(sizeof(t_glb));
	if (!glb)
		panic(glb, CODE_MALLOC, NULL);
	glb->tok = NULL;
	glb->split = NULL;
	glb->rl = NULL;
	glb->old_rval = 0;
	glb->env = env_init(envp);
	if (!glb->env)
		panic(glb, CODE_MALLOC, NULL);
	return (glb);
}

static void	msh_exit(t_glb *glb)
{
	if (!glb)
		return ;
	if (glb->rl)
		free(glb->rl);
	if (glb->tok)
		token_array_destroy(glb->tok);
	if (glb->split)
		token_split_destroy(glb->split);
	if (glb->env)
		env_array_destroy(glb->env, env_array_get_size(glb->env));
	free(glb);
	rl_clear_history();
}

static void	reset(t_glb *glb)
{
	if (glb->tok)
		token_array_destroy(glb->tok);
	if (glb->split)
		token_split_destroy(glb->split);
	if (glb->rl)
		free(glb->rl);
	glb->rl = NULL;
	glb->tok = NULL;
	glb->split = NULL;
}

void	panic(t_glb *glb, int code, t_cmd *cmd)
{
	uint8_t	n;

	n = (uint8_t)code;
	if (cmd)
	{
		close_fd(cmd, glb->multiple_cmd);
		free_t_cmd(cmd, cmd->glb->multiple_cmd);
	}
	msh_exit(glb);
	if (code == CODE_MALLOC)
		f_dprintf(STDERR_FILENO, ERR_MALLOC);
	exit(n);
}

uint8_t	g_rval = 0; /* Global variable init */

int	main(int ac, char *av[], char *ep[])
{
	t_glb	*glb;

	(void) ac;
	(void) av;
	glb = msh_init(ep);
	while (glb)
	{
		reset(glb);
		glb->rl = readline("MSH $ ");
		if (!glb->rl)
			break ;
		if (!*glb->rl)
			continue ;
		add_history(glb->rl);
		glb->tok = token_array_create(glb->rl);
		if (!glb->tok)
			break ;
		if (parsing(glb))
			continue ;
		if (!glb->env)
			break ;
		g_rval = 0;
		exec(glb);
	}
	return (printf("exit\n"), msh_exit(glb), g_rval);
}
