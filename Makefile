# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/11 20:50:51 by pde-masc          #+#    #+#              #
#    Updated: 2025/01/11 20:50:54 by pde-masc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S_NAME	= server
C_NAME	= client

S_BONUS_NAME	= server_bonus
C_BONUS_NAME	= client_bonus

BLUE 	= \033[0;34m
GREEN 	= \033[0;32m
RED 	= \033[0;31m
ORANGE	= \033[38;5;209m
YELLOW	= \033[0;93m
BROWN 	= \033[38;2;184;143;29m
RESET 	= \033[0m

S_SRCS		= server.c
C_SRCS		= client.c

S_BONUS_SRCS	= server_bonus.c
C_BONUS_SRCS	= client_bonus.c

OTHER_SRCS	=	./ft_printf/ft_printf.c ./ft_printf/ft.c ./ft_printf/printchar.c \
				./ft_printf/printhex.c ./ft_printf/printnbr.c ./ft_printf/printud.c \
				./ft_printf/printstr.c ./ft_printf/printptr.c utils.c\

HEADERS  = minitalk.h ./ft_printf/ft_printf.h

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
RM      = rm -rf

S_OBJS	= ${S_SRCS:.c=.o}
C_OBJS	= ${C_SRCS:.c=.o}
OTHER_OBJS	= ${OTHER_SRCS:.c=.o}

S_BONUS_OBJS	= ${S_BONUS_SRCS:.c=.o}
C_BONUS_OBJS	= ${C_BONUS_SRCS:.c=.o}

all: ${S_NAME} ${C_NAME}

${S_NAME}:	$(S_OBJS) ${OTHER_OBJS}
	@${CC} ${S_SRCS} ${OTHER_SRCS} -o ${S_NAME}
	@echo "\n$(GREEN)Created $(S_NAME) ✓ $(RESET)\n"

${C_NAME}:	${C_OBJS} ${OTHER_OBJS}
	@${CC} ${C_SRCS} ${OTHER_SRCS} -o ${C_NAME}
	@echo "\n$(GREEN)Created $(C_NAME) ✓ $(RESET)\n"

%.o: %.c ${HEADERS} Makefile
	@echo "$(BROWN)Compiling   ${BLUE}→   $(YELLOW)$< $(RESET)"
	@${CC} ${CFLAGS} -c -o $@ $<

clean:
	@${RM} ${S_OBJS} ${C_OBJS} ${OTHER_OBJS} ${S_BONUS_OBJS} ${C_BONUS_OBJS}
	@echo "\n${GREEN}Objects cleaned successfully $(RESET)\n"

fclean:		clean
	@${RM} ${S_NAME} ${C_NAME} ${S_BONUS_NAME} ${C_BONUS_NAME}
	@echo "\n${GREEN}Executables cleaned successfully $(RESET)\n"

re: fclean all

bonus: ${S_BONUS_NAME} ${C_BONUS_NAME}

${S_BONUS_NAME}: ${S_BONUS_OBJS} ${OTHER_OBJS}
	@${CC} ${S_BONUS_SRCS} ${OTHER_SRCS} -o ${S_BONUS_NAME}
	@echo "\n$(GREEN)Created $(S_BONUS_NAME) ✓ $(RESET)\n"

${C_BONUS_NAME}: ${C_BONUS_OBJS} ${OTHER_OBJS}
	@${CC} ${C_BONUS_SRCS} ${OTHER_SRCS} -o ${C_BONUS_NAME}
	@echo "\n$(GREEN)Created $(C_BONUS_NAME) ✓ $(RESET)\n"

rebonus: fclean bonus

.PHONY: all clean fclean re
