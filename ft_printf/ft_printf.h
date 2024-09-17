/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:27:26 by pde-masc          #+#    #+#             */
/*   Updated: 2024/02/10 19:30:19 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

// libft functions
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);

// conversion print functions
int		printchar(char c);
int		printstr(char *s);
int		printptr(unsigned long long p);
int		printnbr(int n);
int		printud(unsigned int u);
int		printhex(long n, char c);

// printf
int		ft_printf(const char *input, ...);

#endif
