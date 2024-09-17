/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printhex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:38:53 by pde-masc          #+#    #+#             */
/*   Updated: 2024/02/09 18:53:18 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hexstart(char *hex)
{
	int	i;

	i = 0;
	if (!hex)
		return (0);
	while (hex[i] == '0' && hex[i + 1])
		++i;
	return (i);
}

static char	*dtobin(long n)
{
	char	*bin;
	int		len;

	len = 32;
	bin = (char *)malloc((len + 1) * sizeof(char));
	if (!bin)
		return (NULL);
	bin[len--] = '\0';
	if (++n <= 0)
	{
		while (len >= 0)
		{
			bin[len--] = !((n % 2) * -1) + '0';
			n /= 2;
		}
	}
	else if (--n >= 0)
	{
		while (len >= 0)
		{
			bin[len--] = n % 2 + '0';
			n /= 2;
		}
	}
	return (bin);
}

static int	bintod(char *bin)
{
	return ((bin[0] - '0') * 2 * 2 * 2 + (bin[1] - '0') * 2 * 2 + (bin[2] - '0')
		* 2 + (bin[3] - '0'));
}

static char	*bintohex(char *bin, char *set)
{
	char	*hex;
	char	*sub;
	int		i;
	int		hexlen;

	hexlen = 8;
	hex = (char *)malloc((hexlen + 1) * sizeof(char));
	if (!hex)
		return (NULL);
	i = 0;
	while (i < hexlen)
	{
		sub = ft_substr(bin, i * 4, 4);
		if (!sub)
		{
			free(hex);
			return (NULL);
		}
		hex[i] = set[bintod(sub)];
		free(sub);
		++i;
	}
	hex[hexlen] = '\0';
	return (hex);
}

int	printhex(long n, char c)
{
	char	*bin;
	char	*hex;
	char	*trimmedhex;
	int		retval;

	bin = dtobin(n);
	if (!bin)
		return (-1);
	if (c == 'x')
		hex = bintohex(bin, "0123456789abcdef");
	else
		hex = bintohex(bin, "0123456789ABCDEF");
	if (!hex)
	{
		free(bin);
		return (-1);
	}
	trimmedhex = hex + hexstart(hex);
	retval = printstr(trimmedhex);
	free(bin);
	free(hex);
	return (retval);
}
