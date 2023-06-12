/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:52:26 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/12 13:30:50 by mbarberi         ###   ########.fr       */
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
	while (f_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
		s++;
	while (f_isdigit(*s))
		s++;
	while (f_isspace(*s))
		s++;
	if (!*s)
		return (true);
	return (false);
}

static char	*trim_spaces(char *s)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = f_calloc(f_strlen(s) + 1, sizeof(char));
	if (!new)
		return (NULL);
	if (s[i + 1] && s[i] == '-' && !f_isspace(s[i + 1]))
		new[j++] = s[i++];
	while (s[i] && (f_isspace(s[i]) || s[i] == '0'))
		i++;
	if (s[i] == '+')
		i++;
	while (s[i] && !f_isspace(s[i]))
		new[j++] = s[i++];
	new[j] = 0;
	return (new);
}

static void	blt_exit_update_rval(char **argv)
{
	char		*p;
	char		*q;
	intmax_t	n;

	n = f_exit_atoi(argv[1]);
	p = f_itoa(n);
	q = trim_spaces(argv[1]);
	if (*q == '+')
		q++;
	if (!isnum(argv[1]) || (f_strcmp(q, p)))
	{
		g_rval = 2;
		f_dprintf(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n", argv[1]);
	}
	else
		g_rval = (uint8_t)n;
	free(q);
	free(p);
}

void	blt_exit(t_glb *glb, t_cmd *cmd, int argc, char **argv)
{
	if (argc == 1)
	{
		if (glb->multiple_cmd == 1)
			printf("exit\n");
		panic(glb, glb->old_rval, cmd);
	}
	if (glb->multiple_cmd == 1)
		printf("exit\n");
	if (argc > 2 && isnum(argv[1]))
	{
		g_rval = 1;
		return ((void)f_dprintf(STDERR_FILENO,
				"minishell: exit: too many arguments\n"));
	}
	else
		blt_exit_update_rval(argv);
	panic(glb, g_rval, cmd);
}
