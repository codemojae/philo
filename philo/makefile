# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/31 17:45:49 by hojakim           #+#    #+#              #
#    Updated: 2023/09/30 09:54:54 by hojakim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_PATH	=	./
SRC			=	main.c action.c check_input.c create_thread.c exit_philo.c initialize.c initialize_util.c util.c th_philo.c th_waiter.c th_monitor.c
SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
OBJS		=	$(SRCS:.c=.o)
MAND_NAME	=	philo

OBJ_FILE = $(OBJS)
NAME	= $(MAND_NAME)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_FILE)
		@echo "make $(NAME)"
		@$(CC) $(CFLAGS) $(OBJ_FILE) -o $(NAME)

clean:
	@rm -f $(OBJS) $(BNOBJS)

fclean: 
	@make clean
	@rm -f $(BN_NAME) $(MAND_NAME)

re:
	@make fclean
	@make all

.PHONY : all clean fclean re
