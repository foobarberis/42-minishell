/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:57:10 by mbarberi          #+#    #+#             */
/*   Updated: 2023/02/06 17:50:37 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief The memcmp(3) function compares byte string s1 against byte
 * string s2. Both strings are assumed to be n bytes long.
 * @param s1 First string.
 * @param s2 Second string.
 * @param n The number of bytes to compare.
 * @return The memcmp() function returns an integer less than, equal to, or
* greater than zero if the first n bytes of s1 are found, respectively, to
* be less than, to match, or be greater than the first n bytes of s2*.
*
* For a nonzero return value, the sign is determined by the sign of the
* difference between the first pair of bytes (interpreted as unsigned char)
* that differ in s1 and s2*.
*
* If n is zero, the return value is zero.
 */
int	f_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = s1;
	p2 = s2;
	while (n && *p1 == *p2)
	{
		p1++;
		p2++;
		n--;
	}
	if (n)
		return (*p1 - *p2);
	return (0);
}
