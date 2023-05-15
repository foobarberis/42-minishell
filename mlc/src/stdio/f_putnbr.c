/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_putnbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:35:37 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/13 15:11:26 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief Print the decimal number n in the given base.
 * @param n The number to convert.
 * @param base The base to convert to.
 * @return The number of characters printed.
 */
ssize_t	f_uputnbr(int fd, unsigned int n, char *base)
{
	int		i;
	size_t	l;
	ssize_t	r;
	char	num[32];

	i = 0;
	r = 0;
	l = f_strlen(base);
	while (1)
	{
		num[i++] = base[n % l];
		n /= l;
		if (!n)
			break ;
	}
	while (--i >= 0)
		r += write(fd, &num[i], 1);
	return (r);
}

ssize_t	f_sputnbr(int fd, int n, char *base)
{
	if (n < 0)
		return (write(fd, "-", 1) + f_uputnbr(fd, f_abs(n), base));
	return (f_uputnbr(fd, n, base));
}
