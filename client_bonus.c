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

int	main(int argc, char *argv[])
{
	int		pid;
	char	*message;
	int		i;

	if (argc != 3)
		error_exit("Incorrect input", EXIT_FAILURE);
	pid = ft_atoi2(argv[1]);
	if (pid <= 0)
		error_exit("Incorrect PID input", EXIT_FAILURE);
	if (signal(SIGUSR2, action) == SIG_ERR || signal(SIGUSR1, action) == SIG_ERR)
		error_exit("Error activating signal handlers for server", 1);
	message = argv[2];
	i = -1;
	while (++i < (int)ft_strlen(message))
		send_char(pid, message[i]);
	while (1)
		pause();
	return (0);
}
