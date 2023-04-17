/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:54:06 by mbarberi          #+#    #+#             */
/*   Updated: 2023/02/03 18:22:42 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief The calloc(3) function allocates space for n objects, each m
 * bytes in length.  The result is identical to calling malloc(3) with an
 * argument of 'n * m', with the exception that the allocated memory is
 * explicitly initialized to zero bytes.
 * @param n The number of objects.
 * @param m The size of an object.
 * @return If successful, return a pointer to the allocated memory.  If
 * there is an error, return a NULL pointer.
 */
void	*f_calloc(size_t n, size_t m)
{
	void	*p;

	p = malloc(n * m);
	if (!p)
		return (NULL);
	f_memset(p, 0, n * m);
	return (p);
}
