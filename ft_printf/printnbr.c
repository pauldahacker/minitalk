/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:22:51 by pde-masc          #+#    #+#             */
/*   Updated: 2023/10/10 15:36:56 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printnbr(int n)
{
	char	*to_print;
	int		retval;

	to_print = ft_itoa(n);
	if (!to_print)
		return (-1);
	retval = printstr(to_print);
	free(to_print);
	return (retval);
}
