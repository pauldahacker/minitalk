/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:22:25 by pde-masc          #+#    #+#             */
/*   Updated: 2024/02/14 14:15:13 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	power(int a, int b)
{
	if (b <= 0)
		return (1);
	return (a * power(a, b - 1));
}

void	action(int sig)
{
	static char	c;
	static int	bits;

	c += power(2, bits++) * (sig == SIGUSR1);
	if (bits == 8)
	{
		ft_printf("%c", c);
		c = 0;
		bits = 0;
	}
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	signal(SIGUSR2, action);
	signal(SIGUSR1, action);
	while (1)
		pause();
	return (0);
}
