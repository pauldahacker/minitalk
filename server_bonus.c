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

static void	receive_pid(int sig, int *client_pid)
{
	static unsigned char	c = 0;
	static int				bits = 0;

	c += (1 << bits++) * (sig == SIGUSR1);
	if (bits == 8)
	{
		if (c < '0' || c > '9')
			*client_pid = 0;
		else
			*client_pid = *client_pid * 10 + (c - '0');
		if (kill(*client_pid, 0) == 0)
		{
			if (kill(*client_pid, SIGUSR2) == -1)
				error_exit("Error sending acknowledgment to client", EXIT_FAILURE);
		}
		c = 0;
		bits = 0;
	}
}

static void	reset_server(unsigned char **buf, int *i, int *pid)
{
	if (*buf)
	{
		free(*buf);
		*buf = NULL;
	}
	*i = 0;
	*pid = 0;
}

static void	update_server(unsigned char **buf, int *i, int *client_pid)
{
	if ((*buf)[*i] == '\0')
	{
		ft_printf("%s\n", *buf);
		usleep(1000);
		if (kill(*client_pid, SIGUSR1) == -1)
			error_exit("Error sending acknowledgment to client", EXIT_FAILURE);
		reset_server(buf, i, client_pid);
		return ;
	}
	++(*i);
}

static unsigned char	*get_buffer_mem(unsigned char c, int client_pid)
{
	static int		message_len = 0;
	unsigned char	*buffer;

	if (c == '\0')
	{
		buffer = (unsigned char *)malloc(message_len * sizeof(unsigned char));
		message_len = 0;
		if (!buffer)
			error_exit("Malloc Error", 1);
		usleep(1000);
		if (kill(client_pid, SIGUSR2) == -1)
			error_exit("Error sending acknowledgment to client", EXIT_FAILURE);
		return (buffer);
	}
	message_len = message_len * 10 + (c - '0');
	return (NULL);
}

static void	action(int sig)
{
	static unsigned char	*buffer = NULL;
	static unsigned char	c = 0;
	static int				index = 0;
	static int				bits = 0;
	static int				client_pid = 0;

	if (!client_pid || kill(client_pid, 0) == -1)
		receive_pid(sig, &client_pid);
	else
	{
		c += (1 << bits++) * (sig == SIGUSR1);
		if (bits == 8)
		{
			if (!buffer)
				buffer = get_buffer_mem(c, client_pid);
			else
			{
				buffer[index] = c;
				update_server(&buffer, &index, &client_pid);
			}
			c = 0;
			bits = 0;
		}
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);

	if (signal(SIGUSR2, action) == SIG_ERR
		|| signal(SIGUSR1, action) == SIG_ERR)
		error_exit("Error setting up signal handlers in server", EXIT_FAILURE);
	while (1)
		pause(); // Wait for incoming signals
	return (0);
}
