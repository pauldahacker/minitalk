/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:26:34 by pde-masc          #+#    #+#             */
/*   Updated: 2024/02/14 14:20:15 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include "ft_printf/ft_printf.h"

// this can be found in /proc/sys/kernel/pid_max
# define MAX_PID 4194304

# define INIT_BUF_SIZE 1024

// ft_printf
int		ft_printf(const char *input, ...);

// utils.c
int		ft_atoi2(const char *str);
void	error_exit(char *output, int code);
size_t	ft_strlcpy2(unsigned char *dest, unsigned char *src, size_t size);
void setup_signal(int sig, void (*handler)(int));

#endif
