/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:53:30 by mbarberi          #+#    #+#             */
/*   Updated: 2023/02/06 17:51:45 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief Compute the absolute value of the integer n.
 * @param n The number we want to compute.
 * @return An unsigned integer to ensure that we can compute abs(INT_MIN).
 */
uintmax_t	f_abs(intmax_t n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}
