/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:57:17 by mbarberi          #+#    #+#             */
/*   Updated: 2023/02/06 17:51:38 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief The memmove() function copies n bytes from string s to string d.
 * The two strings may overlap; the copy is always done in a
 * non-destructive manner.
 * d < s
 * s :    foobar
 * d : foobar
 *
 * d > s
 * s : foobar
 * d :    foobar
 * @param d The destination.
 * @param s The source.
 * @param n The number of bytes to copy.
 * @return The original value of d.
 */
void	*f_memmove(void *d, const void *s, size_t n)
{
	unsigned char		*pd;
	const unsigned char	*ps;

	pd = d;
	ps = s;
	if (pd == ps)
		return (pd);
	if (pd < ps)
	{
		while (n)
		{
			*pd++ = *ps++;
			n--;
		}
	}
	else
	{
		while (n)
		{
			n--;
			pd[n] = ps[n];
		}
	}
	return (d);
}
