# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/30 02:33:53 by hojakim           #+#    #+#              #
#    Updated: 2023/08/30 18:56:09 by hojakim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_PATH	=	./
SRC			=	main.c action.c check_input.c create_thread.c exit_philo.c initialize.c util.c
SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
OBJS		=	$(SRCS:.c=.o)
MAND_NAME	=	philo

ifdef BONUS
	OBJ_FILE = $(BNOBJS)
	NAME	= $(BN_NAME)
else
	OBJ_FILE = $(OBJS)
	NAME	= $(MAND_NAME)
endif

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_FILE)
		@echo "make $(NAME)"
		@$(CC) $(CFLAGS) $(OBJ_FILE) -o $(NAME)

bonus:
	@make BONUS=1

clean:
	@rm -f $(OBJS) $(BNOBJS)

fclean: 
	@make clean
	@rm -f $(BN_NAME) $(MAND_NAME)

re:
	@make fclean
	@make all

.PHONY : all clean fclean re bonus
