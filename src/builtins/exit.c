/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:52:26 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/23 15:52:44 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static intmax_t	f_exit_atoi(const char *s)
{
	intmax_t	x;
	intmax_t	sign;

	x = 0;
	sign = 1;
	while (f_isspace(*s))
		s++;
	if (*s == '-')
		sign *= -1;
	if (*s == '-' || *s == '+')
		s++;
	while (f_isdigit(*s))
		x = x * 10 + *s++ - '0';
	return (x * sign);
}

static bool	isnum(char *s)
{
	if (!s || !*s)
		return (false);
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
		if (!f_isdigit(*s++))
			return (false);
	return (true);
}

static void	blt_exit_update_rval(char **argv)
{
	char		*p;
	char		*q;
	intmax_t	n;

	n = f_exit_atoi(argv[1]);
	p = f_itoa(n);
	q = argv[1];
	if (*q == '+')
		q++;
	if (!isnum(argv[1]) || (f_strcmp(q, p)))
	{
		g_rval = 2;
		f_dprintf(STDERR_FILENO, "minishell: exit: numeric argument required\n");
	}
	else
		g_rval = (uint8_t)n;
	free(p);
}

void	blt_exit(t_glb *glb, t_cmd *cmd, int argc, char **argv)
{
	g_rval = 0;
	printf("exit\n");
	if (argc > 2)
	{
		g_rval = 1;
		f_dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
	}
	else if (argc == 2)
		blt_exit_update_rval(argv);
	panic(glb, g_rval, cmd);
}
