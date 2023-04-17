/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:01:22 by mbarberi          #+#    #+#             */
/*   Updated: 2023/02/03 18:22:42 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief strlcpy(3) copies up to n - 1 characters from the string s to d,
 * NUL-terminating the result if n is not 0.
 * @param d The destination string.
 * @param s The source string.
 * @param n The length of d.
 * @return The total length of the string the function tried to create. In
 * this case that means the length of s.
 */
size_t	f_strlcpy(char *d, const char *s, size_t n)
{
	size_t	l;

	l = f_strlen(s);
	if (!n)
		return (l);
	while (--n && *s)
		*d++ = *s++;
	*d = '\0';
	return (l);
}
