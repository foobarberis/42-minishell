/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_strcmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:55:53 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/01 10:59:28 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief The strcmp() function compares the two strings s1 and s2.
 * @return 0, if the s1 and s2 are equal; a negative value if s1 is less
 * than s2; a positive value if s1 is greater than s2.
 */
int	f_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
