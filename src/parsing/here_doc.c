/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:33:31 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/12 15:27:56 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_handler(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_done = 1;
	g_rval = (uint8_t)(128 + sig);
}

static int	event(void)
{
	return (0);
}

static char	*here_doc_loop(char *here_doc, char *rl, char *tmp, char *lim)
{
	while (1)
	{
		free(rl);
		rl_event_hook = event;
		rl = readline("> ");
		if (g_rval == 130)
			break ;
		if (!rl)
			f_dprintf(STDERR_FILENO,
				"minishell: warning: here-document delimited "
				"by end-of-file (wanted `%s')\n", lim);
		if (!rl || !f_strcmp(rl, lim))
			break ;
		tmp = f_strjoin(here_doc, rl);
		if (!tmp)
			return (free(here_doc), free(rl), NULL);
		free(here_doc);
		here_doc = f_strjoin(tmp, "\n");
		free(tmp);
		if (!here_doc)
			return (free(rl), NULL);
	}
	free(rl);
	return (here_doc);
}

char	*here_doc(char *lim)
{
	char	*buf[3];

	buf[0] = f_strdup("");
	if (!buf[0])
		return (NULL);
	buf[1] = NULL;
	buf[2] = NULL;
	signal(SIGINT, here_doc_handler);
	return (here_doc_loop(buf[0], buf[1], buf[2], lim));
}
