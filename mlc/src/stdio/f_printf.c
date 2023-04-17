/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:19:38 by mbarberi          #+#    #+#             */
/*   Updated: 2023/02/06 17:28:20 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"
#include <stdarg.h>

#define BASE10 "0123456789"
#define BASE16UP "0123456789ABCDEF"
#define BASE16LOW "0123456789abcdef"

static int	f__putchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

static int	f__putstr(char *s)
{
	if (!s)
		return (write(STDOUT_FILENO, "(null)", 6));
	return (write(STDOUT_FILENO, s, f_strlen(s)));
}

static int	f__putnbr(int n)
{
	if (n < 0)
	{
		f__putchar('-');
		return (f_putnbr_base(f_abs(n), BASE10) + 1);
	}
	return (f_putnbr_base(f_abs(n), BASE10));
}

/**
 * @brief Print the argument according to format specified by c.
 * @param c The character following a % in the format string.
 * @param ap The list of variable arguments.
 * @return The number of characters printed.
 */
static int	f__print_arg(char c, va_list *ap)
{
	if (c == 'c')
		return (f__putchar(va_arg(*ap, int)));
	if (c == 's')
		return (f__putstr(va_arg(*ap, char *)));
	if (c == 'p')
	{
		f__putstr("0x");
		return (f_putnbr_base(va_arg(*ap, size_t), BASE16LOW) + 2);
	}
	if (c == 'd' || c == 'i')
		return (f__putnbr(va_arg(*ap, int)));
	if (c == 'u')
		return (f_putnbr_base(va_arg(*ap, unsigned int), BASE10));
	if (c == 'x')
		return (f_putnbr_base(va_arg(*ap, unsigned int), BASE16LOW));
	if (c == 'X')
		return (f_putnbr_base(va_arg(*ap, unsigned int), BASE16UP));
	if (c == '%')
		return (f__putchar('%'));
	return (f__putchar(c));
}

/**
 * @brief Produce output according to a format specified in the string s and
 * write this output to stdout.
 * @param s The format string.
 * @return The number of characters printed if the function returns
 * successfully, else it returns a negative value.
 */
int	f_printf(const char *s, ...)
{
	int		r;
	va_list	ap;

	if (!s || write(1, 0, 0) < 0)
		return (-1);
	if (!*s)
		return (0);
	r = 0;
	va_start(ap, s);
	while (*s)
	{
		if (*s != '%')
			r += f__putchar(*s);
		else
			r += f__print_arg(*++s, &ap);
		if (!*s++)
			break ;
	}
	va_end(ap);
	return (r);
}
