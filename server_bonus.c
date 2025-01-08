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
	static unsigned char	c;
	static int				bits;
	static int				pid_flag;
	static int				pid;

	c += (1 << bits++) * (sig == SIGUSR1);
	if (bits == 8)
	{
		if (c == '\0' && !pid_flag)
			pid_flag = 1;
		else if (c == '\0' && pid_flag)
		{
			if (kill(pid, SIGUSR1) == -1)
				error_exit("Error sending a signal", EXIT_FAILURE);
			pid = 0;
			pid_flag = 0;
			ft_printf("\n");
		}
		else if (pid_flag == 0)
			pid = pid * 10 + (c - '0');
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
