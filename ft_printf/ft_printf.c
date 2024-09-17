/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:00:11 by pde-masc          #+#    #+#             */
/*   Updated: 2024/02/09 18:10:51 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_conv(char c, va_list args)
{
	if (c == '%')
		return (printchar('%'));
	if (c == 'c')
		return (printchar(va_arg(args, int)));
	if (c == 's')
		return (printstr(va_arg(args, char *)));
	if (c == 'p')
		return (printptr(va_arg(args, unsigned long long)));
	if (c == 'd' || c == 'i')
		return (printnbr(va_arg(args, int)));
	if (c == 'u')
		return (printud(va_arg(args, unsigned int)));
	if (c == 'x' || c == 'X')
		return (printhex(va_arg(args, long), c));
	return (0);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	int		retval;
	int		temp;

	if (!input)
		return (0);
	retval = 0;
	va_start(args, input);
	while (*input)
	{
		temp = retval;
		if (*input == '%' && *(input + 1))
		{
			retval += handle_conv(*(input + 1), args);
			input += 2;
		}
		else
			retval += printchar(*(input++));
		if (temp > retval)
			return (-1);
	}
	va_end(args);
	return (retval);
}
