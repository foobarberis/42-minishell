/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:01:15 by mbarberi          #+#    #+#             */
/*   Updated: 2023/02/03 18:22:42 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief Allocates (with malloc(3)) and returns a new string, which is the
 * result of the concatenation of 's1' and 's2'.
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return The new string or NULL if the allocation fails.
 */
char	*f_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	l1 = f_strlen(s1);
	l2 = f_strlen(s2);
	p = malloc(l1 + l2 + 1);
	if (!p)
		return (NULL);
	f_strlcpy(p, s1, l1 + 1);
	p += l1;
	f_strlcpy(p, s2, l2 + 1);
	return (p - l1);
}
