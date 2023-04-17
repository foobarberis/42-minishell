/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:01:36 by mbarberi          #+#    #+#             */
/*   Updated: 2023/02/03 18:22:42 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief The strnstr(3) function locates the first occurrence of the
 * NUL-terminated string n in the string h, where not more than m
 * characters are searched.
 * @param h The string to search (haystack).
 * @param n The string to find (needle).
 * @param m The maximum number of characters to scan.
 * @return  h if n is an empty string; if n occurs nowhere in h, NULL is
 * returned; otherwise a pointer to the first character of the first
 * occurrence of n is returned.
 */
char	*f_strnstr(const char *h, const char *n, size_t m)
{
	size_t	i;
	size_t	j;

	if (!*n)
		return ((char *)(h));
	i = 0;
	while (i < m && h[i])
	{
		j = 0;
		while ((i + j) < m && n[j] == h[i + j])
		{
			j++;
			if (!n[j])
				return ((char *)(h + i));
		}
		i++;
	}
	return (NULL);
}
