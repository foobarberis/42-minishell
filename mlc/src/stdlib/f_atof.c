/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:11:17 by mbarberi          #+#    #+#             */
/*   Updated: 2023/02/16 14:21:58 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/* Compute the decimal part of the string */
static double	f_atof__dec(const char *s)
{
	double	y;
	double	scale;

	y = 0;
	scale = 10;
	if (*s && *s == '.')
	{
		s++;
		while (*s && f_isdigit(*s))
		{
			y += (*s++ - '0') / scale;
			scale *= 10;
		}
	}
	return (y);
}

/**
 * @brief The atof(3) function converts the initial portion of the string
 * pointed to by s to double.
 * @param s The string to convert.
 * @return A double corresponding to s. If an error occured during the
 * processing of the string (if the string contains non-digit characters
 * for example) return the number computed up to the point the error
 * occured.
 */
double	f_atof(const char *s)
{
	double	x;
	double	sign;

	x = 0;
	sign = 1;
	while (f_isspace(*s))
		s++;
	if (*s == '-')
		sign *= -1;
	if (*s == '-' || *s == '+')
		s++;
	while (*s && f_isdigit(*s))
		x = x * 10 + *s++ - '0';
	return ((x + f_atof__dec(s)) * sign);
}
