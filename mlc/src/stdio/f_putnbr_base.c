/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_putnbr_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:35:37 by mbarberi          #+#    #+#             */
/*   Updated: 2023/03/04 16:38:49 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief Print the decimal number n in the given base.
 * @param n The number to convert.
 * @param base The base to convert to.
 * @return The number of characters printed.
 */
int	f_putnbr_base(uint64_t n, char *base)
{
	int		i;
	int		l;
	int		r;
	char	num[32];

	i = 0;
	r = 0;
	l = f_strlen(base);
	if (!n)
		return (write(STDOUT_FILENO, &base[0], 1));
	while (n)
	{
		num[i++] = base[n % l];
		n /= l;
	}
	while (--i >= 0)
		r += write(STDOUT_FILENO, &num[i], 1);
	return (r);
}
