/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printud.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:35:48 by pde-masc          #+#    #+#             */
/*   Updated: 2023/10/10 15:37:57 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	count_digits(unsigned int u)
{
	if (!u)
		return (0);
	return (1 + count_digits(u / 10));
}

static char	*utoa(unsigned int u)
{
	char	*res;
	size_t	len;

	len = count_digits(u) + (u == 0);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (!u)
		res[0] = '0';
	while (u)
	{
		res[--len] = u % 10 + '0';
		u /= 10;
	}
	return (res);
}

int	printud(unsigned int u)
{
	char	*to_print;
	int		retval;

	to_print = utoa(u);
	if (!to_print)
		return (-1);
	retval = printstr(to_print);
	free(to_print);
	return (retval);
}
