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

void	send_char(int pid, char c)
{
	int		pos;
	char	tmp;

	pos = -1;
	while (++pos < CHAR_BIN_SIZE)
	{
		tmp = c >> pos;
		if (tmp % 2)
			kill(pid, SIGUSR1);
		if (tmp % 2 == 0)
			kill(pid, SIGUSR2);
		usleep(100);
	}
}

int	main(int argc, char *argv[])
{
	int		pid;
	char	*message;
	int		i;

	if (argc != 3)
	{
		ft_printf("Input Error\nExpected: ./client (PID) (MESSAGE)\n");
		exit(1);
	}
	pid = ft_atoi(argv[1]);
	message = argv[2];
	i = -1;
	while (++i < (int)ft_strlen(message))
		send_char(pid, message[i]);
	return (0);
}
