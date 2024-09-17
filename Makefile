SERVER_NAME	= server
CLIENT_NAME	= client

BLUE 	= \033[0;34m
GREEN 	= \033[0;32m
RED 	= \033[0;31m
ORANGE	= \033[38;5;209m
YELLOW	= \033[0;93m
BROWN 	= \033[38;2;184;143;29m
RESET 	= \033[0m

SERVER_SRCS		= server.c

CLIENT_SRCS		= client.c

OTHER_SRCS	=	./ft_printf/ft_printf.c ./ft_printf/ft.c ./ft_printf/printchar.c \
				./ft_printf/printhex.c ./ft_printf/printnbr.c ./ft_printf/printud.c \
				./ft_printf/printstr.c ./ft_printf/printptr.c utils.c\

HEADERS  = minitalk.h ./ft_printf/ft_printf.h

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
RM      = rm -rf

%.o:    %.c
	@echo "$(BROWN)Compiling   ${BLUE}→   $(YELLOW)$< $(RESET)"
	@${CC} ${CFLAGS} -c -o $@ $<

SERVER_OBJS	= ${SERVER_SRCS:.c=.o}
CLIENT_OBJS	= ${CLIENT_SRCS:.c=.o}
OTHER_OBJS	= ${OTHER_SRCS:.c=.o}

all: ${SERVER_NAME} ${CLIENT_NAME}

${SERVER_NAME}:	$(SERVER_OBJS) ${OTHER_OBJS} $(HEADERS)
	@${CC} ${SERVER_SRCS} ${OTHER_SRCS} -o ${SERVER_NAME}
	@echo "\n$(GREEN)Created $(SERVER_NAME) ✓ $(RESET)\n"

${CLIENT_NAME}:	${CLIENT_OBJS} ${OTHER_OBJS} ${HEADERS}
	@${CC} ${CLIENT_SRCS} ${OTHER_SRCS} -o ${CLIENT_NAME}
	@echo "\n$(GREEN)Created $(CLIENT_NAME) ✓ $(RESET)\n"

clean:
	${RM} ${SERVER_OBJS} ${CLIENT_OBJS} ${OTHER_OBJS}
	@echo "\n${GREEN}Objects cleaned successfully $(RESET)\n"

fclean:		clean
	@${RM} ${SERVER_NAME} ${CLIENT_NAME} */*.o
	@echo "\n${GREEN}Objects and executables cleaned successfully $(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
