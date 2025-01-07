/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:37:48 by pde-masc          #+#    #+#             */
/*   Updated: 2024/02/09 18:41:49 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	is_space(int c)
{
	return (c == '\t' || c == '\n' || c == ' '
		|| c == '\f' || c == '\r' || c == '\v');
}

// never goes above MAX_PID
int	ft_atoi2(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*str && is_space(*str))
		++str;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			sign = -1;
		++str;
	}
	if (!*str || *str < '0' || *str > '9')
		return (0);
	while (*(str + 1) && *(str + 1) >= '0' && *(str + 1) <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > MAX_PID)
			return (0);
		++str;
	}
	return (sign * result * 10 + sign * (*str - '0'));
}

void	error_exit(char *output, int code)
{
	while (output && *output)
		write(STDERR_FILENO, output++, 1);
	write(STDERR_FILENO, "\n", 1);
	exit(code);
}
