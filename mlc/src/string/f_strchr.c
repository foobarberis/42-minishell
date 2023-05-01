/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_strchr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:12:14 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/01 10:33:24 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief The strchr() function returns a pointer to the first occurrence
 * of the character c in the string s.
 * @param s The string to search.
 * @param c The character to find.
 * @return A pointer to the matched character or NULL if the character is
 * not found.
 */
char	*f_strchr(const char *s, int c)
{
	return (f_memchr(s, c, f_strlen(s) + 1));
}
