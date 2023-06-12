/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:32:38 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/12 19:37:27 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	f_ndigit(intmax_t n, int baselen)
{
	size_t	l;

	l = 0;
	if (n <= 0)
		l += 1;
	while (n)
	{
		l++;
		n /= baselen;
	}
	return (l);
}

char	*f_itoa(intmax_t n)
{
	char		*s;
	size_t		l;
	uintmax_t	nb;

	l = f_ndigit(n, 10);
	s = malloc(l + 1);
	if (!s)
		return (NULL);
	s[l] = '\0';
	if (n < 0)
		s[0] = '-';
	else if (!n)
		s[0] = '0';
	nb = f_abs(n);
	while (nb)
	{
		s[--l] = (char)(nb % 10 + '0');
		nb /= 10;
	}
	return (s);
}

int	ismeta(int c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	is_legal(int c)
{
	return (f_isalnum(c) || c == '_' || c == '?' || c == 0);
}
