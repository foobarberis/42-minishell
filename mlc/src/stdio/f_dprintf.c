/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_dprintf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:40:35 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/13 16:41:43 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"
#include <stdarg.h>

/**
 * @brief Produce output according to a format specified in the string s and
 * write this output to fd.
 * @param s The format string.
 * @return The number of characters printed if the function returns
 * successfully, else it returns a negative value.
 */
int	f_dprintf(int fd, const char *s, ...)
{
	ssize_t	r;
	va_list	ap;

	if (!s || fd < 0 || write(fd, 0, 0) < 0)
		return (-1);
	if (!*s)
		return (0);
	r = 0;
	va_start(ap, s);
	while (*s)
	{
		if (*s != '%')
			r += printf__putchar(fd, *s);
		else
			r += printf__arg(fd, *++s, &ap);
		if (!*s++)
			break ;
	}
	va_end(ap);
	return ((int)r);
}
