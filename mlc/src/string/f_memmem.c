/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_memmem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:53:27 by mbarberi          #+#    #+#             */
/*   Updated: 2023/03/05 15:51:38 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief The memmem(3) function locates the first occurrence of the byte
 * string n (needle) in the byte string h (haystack).
 * @param h0 The byte string to search.
 * @param hlen The length of h.
 * @param n0 The byte string to find.
 * @param nlen The length of n.
 * @return If hlen is smaller than nlen, if nlen is 0, if
 * hlen is 0 or if n occurs nowhere in h, NULL is returned;
 * otherwise a pointer to the first character of the first occurrence of
 * n is returned.
 */
void	*f_memmem(const void *h0, size_t hlen, const void *n0, size_t nlen)
{
	unsigned char			*cur;
	unsigned char			*last;
	const unsigned char		*h;
	const unsigned char		*n;

	h = h0;
	n = n0;
	if (hlen < nlen || !hlen || !nlen)
		return (NULL);
	if (nlen == 1)
		return (f_memchr(h0, (int)*n, hlen));
	cur = (unsigned char *)h;
	last = (unsigned char *)h + (hlen - nlen);
	while (cur <= last)
	{
		if (cur[0] == n[0] && f_memcmp(cur, n, nlen) == 0)
			return (cur);
		cur++;
	}
	return (NULL);
}
