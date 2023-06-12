/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:45:35 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/31 14:24:34 by mbarberi         ###   ########.fr       */
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
	(void) sig;
}

void	sig_child_handler(int status)
{
	if (WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		g_rval = (uint8_t)(128 + SIGINT);
	}
	else if (WTERMSIG(status) == SIGQUIT)
	{
		write(2, "Quit\n", 6);
		g_rval = (uint8_t)(128 + SIGQUIT);
	}
}
