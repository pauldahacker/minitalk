/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:22:25 by pde-masc          #+#    #+#             */
/*   Updated: 2025/01/11 20:50:35 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_server_state = WAITING_FOR_PID;

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
		if (*client_pid && kill(*client_pid, 0) == 0)
		{
			usleep(5000);
			g_server_state = WAITING_FOR_MSG_LENGTH;
			if (kill(*client_pid, SIGUSR2) == -1)
				error_exit("Error sending PID acknowledgment", EXIT_FAILURE);
		}
	}
}

static unsigned char	*get_buffer_mem(unsigned char c, int client_pid)
{
	static int		message_len = 0;
	unsigned char	*buffer;

	if (c)
		message_len = message_len * 10 + (c - '0');
	usleep(200);
	if (c && kill(client_pid, SIGUSR2) == -1)
		error_exit("Error sending bit acknowledgment", EXIT_FAILURE);
	if (c == '\0')
	{
		buffer = (unsigned char *)malloc(message_len * sizeof(unsigned char));
		if (!buffer)
			error_exit("Malloc Error", 1);
		message_len = 0;
		g_server_state = WAITING_FOR_MSG;
		if (kill(client_pid, SIGUSR2) == -1)
			error_exit("Error sending length acknowledgment", EXIT_FAILURE);
		return (buffer);
	}
	return (NULL);
}

static void	update_server(unsigned char *c, unsigned char **buf,
	int *i, int *client_pid)
{
	if (g_server_state == WAITING_FOR_MSG)
	{
		(*buf)[(*i)++] = *c;
		usleep(200);
		if (*c && kill(*client_pid, SIGUSR2) == -1)
			error_exit("Error sending bit acknowledgment", EXIT_FAILURE);
		if (*c == '\0')
		{
			ft_printf("%s\n", *buf);
			free(*buf);
			*buf = NULL;
			*i = 0;
			g_server_state = WAITING_FOR_PID;
			if (kill(*client_pid, SIGUSR1) == -1)
				error_exit("Error sending msg acknowledgment", EXIT_FAILURE);
			*client_pid = 0;
		}
	}
	else
		*buf = get_buffer_mem(*c, *client_pid);
	*c = 0;
}

static void	server_action(int sig)
{
	static unsigned char	*buffer = NULL;
	static unsigned char	c = 0;
	static int				index = 0;
	static int				bits = 0;
	static int				client_pid = 0;

	if (g_server_state == WAITING_FOR_PID)
		receive_pid(sig, &client_pid);
	else
	{
		c += (1 << bits++) * (sig == SIGUSR1);
		if (bits != 8)
		{
			usleep(200);
			if (kill(client_pid, SIGUSR2) == -1)
				error_exit("Error sending bit acknowledgment", EXIT_FAILURE);
		}
		if (bits == 8)
		{
			bits = 0;
			update_server(&c, &buffer, &index, &client_pid);
		}
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	signal(SIGUSR2, server_action);
	signal(SIGUSR1, server_action);
	while (1)
		pause();
	return (0);
}
