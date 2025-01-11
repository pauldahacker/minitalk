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

size_t	ft_strlcpy2(unsigned char *dest, unsigned char *src, size_t size)
{
	size_t	i;
	size_t	result;

	i = 0;
	result = ft_strlen((const char *)src);
	if (size == 0)
		return (result);
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (result);
}

void setup_signal(int sig, void (*handler)(int))
{
    struct sigaction sa;

    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    if (sigaction(sig, &sa, NULL) == -1)
        error_exit("Error setting up signal handler", EXIT_FAILURE);
}