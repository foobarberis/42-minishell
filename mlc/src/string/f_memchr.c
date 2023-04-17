/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:57:06 by mbarberi          #+#    #+#             */
/*   Updated: 2023/02/06 17:51:08 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief The memchr(3) function locates the first occurrence of c
 * (converted to an unsigned char) in string s.
 * @param s The string to search.
 * @param c The byte to find.
 * @param n The number of bytes to scan.
 * @return A pointer to the byte located, or NULL if no such byte
 * exists within n bytes.
 */
void	*f_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ps;

	ps = s;
	c = (unsigned char)c;
	while (n && (*ps != c))
	{
		ps++;
		n--;
	}
	if (n)
		return ((void *)ps);
	return (NULL);
}
