# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hojakim <hojakim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/31 17:45:49 by hojakim           #+#    #+#              #
#    Updated: 2023/09/30 09:52:42 by hojakim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_PATH	=	./
SRC			=	main action check_input create_process exit_philo initialize monitor philo_action util
SRCS		=	$(addsuffix _bonus.c, $(addprefix $(SRC_PATH), $(SRC)))
OBJS		=	$(SRCS:.c=.o)
MAND_NAME	=	philo_bonus

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
