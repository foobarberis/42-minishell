/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vburton <vburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:51:54 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/30 14:20:10 by vburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	contains_valid_option(char *s)
{
	if (f_strlen(s) < 2)
		return (false);
	if ((*s == '-') && (*(s + 1) == 'n'))
	{
		s++;
		while (*s && *s == 'n')
			s++;
	}
	if (!*s)
		return (true);
	return (false);
}

void	blt_echo(char **argv)
{
	bool	newline;
	size_t	i;

	g_rval = 0;
	if (!argv || !argv[1])
	{
		printf("\n");
		return ;
	}
	i = 1;
	newline = true;
	while (contains_valid_option(argv[i]))
	{
		newline = false;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i])
			printf(" ");
	}
	if (newline)
		printf("\n");
}
