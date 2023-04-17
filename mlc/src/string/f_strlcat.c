/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:01:19 by mbarberi          #+#    #+#             */
/*   Updated: 2023/02/06 17:51:55 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief The strlcat(3) function appends the NUL-terminated string s to
 * the end of d. It will append at most n - strlen(d) - 1 bytes,
 * NUL-terminating the result. d and s must not overlap.
 * @param d The destination.
 * @param s The source.
 * @param n The destination's size.
 * @return The total length of the string the function tried to create.
 * That means the initial length of d plus the length of s.
 */
size_t	f_strlcat(char *d, const char *s, size_t n)
{
	size_t	l;

	l = f_strnlen(d, n);
	if (l == n)
		return (l + f_strlen(s));
	return (l + f_strlcpy(d + l, s, n - l));
}
