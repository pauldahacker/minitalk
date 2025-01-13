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

static void	client_action(int sig)
{
	(void)sig;
	return ;
}

static void	send_byte(int dest_pid, unsigned char byte, int info_sent)
{
	int	pos;
	int	bit;

	pos = -1;
	while (++pos < CHAR_BIT)
	{
		bit = byte >> pos;
		if ((bit % 2) && kill(dest_pid, SIGUSR1) == -1)
			error_exit("Error sending SIGUSR1 from client", EXIT_FAILURE);
		else if (!(bit % 2) && kill(dest_pid, SIGUSR2) == -1)
			error_exit("Error sending SIGUSR2 from client", EXIT_FAILURE);
		if (info_sent)
			pause();
		else
			usleep(1000);
	}
}

static void	send_int(int dest_pid, int num, int pid_sent)
{
	int				divisor;
	unsigned char	byte_to_send;

	divisor = 1;
	while (num / divisor >= 10)
		divisor *= 10;
	while (divisor)
	{
		byte_to_send = num / divisor + '0';
		send_byte(dest_pid, byte_to_send, pid_sent);
		num = num % divisor;
		divisor /= 10;
	}
	if (pid_sent)
		send_byte(dest_pid, '\0', 1);
}

static void	send_message(int dest_pid, char *msg)
{
	int	i;
	int	msg_len;

	msg_len = (int)ft_strlen(msg);
	i = -1;
	while (++i < msg_len)
		send_byte(dest_pid, (unsigned char)msg[i], 1);
	send_byte(dest_pid, '\0', 1);
}

int	main(int argc, char *argv[])
{
	int		server_pid;
	int		client_pid;

	if (argc != 3)
		error_exit("Usage: ./client <server_pid> <message>", EXIT_FAILURE);
	server_pid = ft_atoi2(argv[1]);
	if (server_pid <= 0 || kill(server_pid, 0) == -1)
		error_exit("Invalid or unreachable server PID", EXIT_FAILURE);
	signal(SIGUSR2, client_action);
	signal(SIGUSR1, client_action);
	client_pid = getpid();
	send_int(server_pid, client_pid, 0);
	pause();
	send_int(server_pid, ft_strlen(argv[2]), 1);
	send_message(server_pid, argv[2]);
	return (0);
}
