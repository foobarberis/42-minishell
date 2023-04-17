/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:57:14 by mbarberi          #+#    #+#             */
/*   Updated: 2023/02/06 17:50:57 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief The memcpy(3) function copies n bytes from memory area s to
 * memory area d.  If d and s overlap, behavior is undefined. Applications
 * in which d and s might overlap should use memmove(3) instead.
 * @param d The destination.
 * @param s The source.
 * @param n The number of bytes to copy.
 * @return The original value of d.
 */
void	*f_memcpy(void *d, const void *s, size_t n)
{
	unsigned char		*pd;
	const unsigned char	*ps;

	pd = d;
	ps = s;
	while (n--)
		*pd++ = *ps++;
	return (d);
}
