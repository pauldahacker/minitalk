/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:22:09 by pde-masc          #+#    #+#             */
/*   Updated: 2024/02/10 19:26:28 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_char(int pid, char c)
{
	int	pos;
	int	bit;

	pos = -1;
	while (++pos < CHAR_BIT)
	{
		bit = c >> pos;
		if ((bit % 2) && kill(pid, SIGUSR1) == -1)
			error_exit("Error sending a signal", EXIT_FAILURE);
		if (!(bit % 2) && kill(pid, SIGUSR2) == -1)
			error_exit("Error sending a signal", EXIT_FAILURE);
		usleep(100);
	}
}

static void	send_msg(int pid, char *msg)
{
	int	i;

	i = -1;
	while (++i < (int)ft_strlen(msg))
		send_char(pid, msg[i]);
	send_char(pid, '\0');
}

int	main(int argc, char *argv[])
{
	int		pid;

	if (argc != 3)
		error_exit("Incorrect input", EXIT_FAILURE);
	pid = ft_atoi2(argv[1]);
	if (pid <= 0)
		error_exit("Incorrect PID input", EXIT_FAILURE);
	send_msg(pid, argv[2]);
	return (0);
}
