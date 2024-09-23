# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 16:55:40 by mariaoli          #+#    #+#              #
#    Updated: 2024/09/23 19:25:54 by mariaoli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c \
		check_args.c \
		time_utils.c \
		init_utils.c \
		routine.c \
		actions.c \
		actions_utils.c \
		monitoring.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=thread
#CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

RM = rm -f

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re