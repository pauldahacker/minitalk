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

static void	action(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("Message was successfully received by server!\n");
	return ;
}

static void	send_byte(int pid, unsigned char byte)
{
	int	pos;
	int	bit;

	pos = -1;
	while (++pos < CHAR_BIT)
	{
		bit = byte >> pos;
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
		send_byte(pid, (unsigned char)msg[i]);
	send_byte(pid, '\0');
}

int	main(int argc, char *argv[])
{
	int		server_pid;
	char	*pid_string;

	if (argc != 3)
		error_exit("Incorrect input", EXIT_FAILURE);
	server_pid = ft_atoi2(argv[1]);
	if (server_pid <= 0)
		error_exit("Incorrect PID input", EXIT_FAILURE);
	if (signal(SIGUSR1, action) == SIG_ERR)
		error_exit("Error activating signal handler for client bonus", 1);
	pid_string = ft_itoa(getpid());
	if (!pid_string)
		error_exit("Malloc Error", EXIT_FAILURE);
	send_msg(server_pid, pid_string);
	free(pid_string);
	send_msg(server_pid, argv[2]);
	return (0);
}
