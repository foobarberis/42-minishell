/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:37:03 by mbarberi          #+#    #+#             */
/*   Updated: 2023/02/06 17:50:25 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief The memrchr() function locates the last occurrence of c
 * (converted to an unsigned char) in string s.
 * @param s The string to search.
 * @param c The byte to find.
 * @param n The number of bytes to scan.
 * @return A pointer to the byte located, or NULL if no such byte
 * exists within n bytes.
 */
void	*f_memrchr(const void *s, int c, size_t n)
{
	const unsigned char	*ps;

	ps = s;
	c = (unsigned char)c;
	while (n--)
		if (ps[n] == c)
			return ((void *)(ps + n));
	return (NULL);
}
