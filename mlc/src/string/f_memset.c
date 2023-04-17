/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:57:20 by mbarberi          #+#    #+#             */
/*   Updated: 2023/02/03 18:22:42 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief The memset(3) function writes len bytes of value c (converted to
 * an unsigned char) to the string b.
 * @param s The string to write to.
 * @param c The value to write.
 * @param n The number of bytes to write.
 * @return Its first argument.
 */
void	*f_memset(void *s, int c, size_t n)
{
	unsigned char	*ps;

	ps = s;
	while (n--)
		*ps++ = (unsigned char)c;
	return (s);
}
