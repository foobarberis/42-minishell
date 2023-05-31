/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:45:35 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/31 14:37:30 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_rval = (uint8_t)(128 + sig);
}

void	sigquit_handler(int sig)
{
	(void)sig;
}

void sig_child_handler(int sig, int status)
{
	if (WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		g_rval = (uint8_t)(128 + SIGINT);
	}
	else if (WTERMSIG(status) == SIGQUIT)
	{
		write(1, "Quit\n", 5);
		g_rval = (uint8_t)(128 + SIGQUIT);
	}
}