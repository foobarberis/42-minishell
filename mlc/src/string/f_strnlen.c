/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_strnlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:11:31 by mbarberi          #+#    #+#             */
/*   Updated: 2023/03/04 14:22:03 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief The strnlen(3) function attempts to compute the length of s, but
 * never scans beyond the first n bytes of s.
 * @param s A string.
 * @param n The maximum number of bytes to scan.
 * @return Either the same result as strlen(3) or n, whichever is smaller.
 */
size_t	f_strnlen(const char *s, size_t n)
{
	const char	*p;

	p = f_memchr(s, 0, n);
	if (p)
		return (p - s);
	return (n);
}
