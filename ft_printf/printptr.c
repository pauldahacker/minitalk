/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:21:50 by pde-masc          #+#    #+#             */
/*   Updated: 2023/10/10 15:37:47 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ptrlen(unsigned long long p)
{
	if (!p)
		return (0);
	return (1 + ptrlen(p / 16));
}

static char	*ptoa(unsigned long long p, char *set)
{
	char	*a;
	int		plen;

	plen = ptrlen(p);
	a = (char *)malloc((plen + 1) * sizeof(char));
	if (!a)
		return (NULL);
	a[plen--] = '\0';
	while (p)
	{
		a[plen--] = set[p % 16];
		p /= 16;
	}
	return (a);
}

int	printptr(unsigned long long p)
{
	int		retval;
	char	*a;

	if (printstr("0x") == -1)
		return (-1);
	if (!p)
	{
		if (printstr("0") == -1)
			return (-1);
		return (3);
	}
	a = ptoa(p, "0123456789abcdef");
	if (!a)
		return (-1);
	retval = printstr(a);
	free(a);
	if (retval == -1)
		return (-1);
	return (retval + 2);
}
