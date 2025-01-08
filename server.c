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

static void	action(int sig)
{
	static char	c;
	static int	bits;

	c += (1 << bits++) * (sig == SIGUSR1);
	if (bits == 8)
	{
		if (c == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", c);
		c = 0;
		bits = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	if (signal(SIGUSR2, action) == SIG_ERR
		|| signal(SIGUSR1, action) == SIG_ERR)
		error_exit("Error activating signal handlers", 1);
	while (1)
		pause();
	return (0);
}
