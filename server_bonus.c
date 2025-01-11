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
		c = 0;
		bits = 0;
	}
}

static void	update_server(unsigned char *c, unsigned char **buf, int *i, int *client_pid)
{
	(*buf)[(*i)++] = *c;
	if (*c == '\0')
	{
		ft_printf("%s\n", *buf);
		free(*buf);
		*buf = NULL;
		*i = 0;
		usleep(500);
		if (kill(*client_pid, SIGUSR1) == -1)
			error_exit("Error sending acknowledgment 1 to client", EXIT_FAILURE);
		*client_pid = 0;
	}
	*c = 0;
}

static unsigned char	*get_buffer_mem(unsigned char *c, int client_pid)
{
	static int		message_len = 0;
	unsigned char	*buffer;

	//ft_printf("msg len: %d\n", message_len);
	if (*c == '\0')
	{
		buffer = (unsigned char *)malloc(message_len * sizeof(unsigned char));
		if (!buffer)
			error_exit("Malloc Error", 1);
		message_len = 0;
		usleep(500);
		if (kill(client_pid, SIGUSR2) == -1)
			error_exit("Error sending acknowledgment to client", EXIT_FAILURE);
		return (buffer);
	}
	else
		message_len = message_len * 10 + (*c - '0');
	*c = 0;
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
		usleep(200);
		if (kill(client_pid, SIGUSR2) == -1)
			error_exit("Error sending acknowledgment to client", EXIT_FAILURE);
		if (bits == 8)
		{
			bits = 0;
			if (buffer)
				update_server(&c, &buffer, &index, &client_pid);
			else
				buffer = get_buffer_mem(&c, client_pid);
		}
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	setup_signal(SIGUSR2, action);
	setup_signal(SIGUSR1, action);
	while (1)
		pause();
	return (0);
}
