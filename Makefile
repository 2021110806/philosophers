# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjeon2 <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/17 20:52:41 by minjeon2          #+#    #+#              #
#    Updated: 2023/08/17 20:52:43 by minjeon2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
NAME = philo
LIBFT = ./libft/libft.a
LIBFT_DIR = libft
SRCS = main.c utils.c acting.c philo_monitor.c list_maker.c
OBJS = $(SRCS:.c=.o)

.PHONY : clean fclean re all bonus

all: $(NAME)

clean:
	make -C $(LIBFT_DIR) fclean
	rm -f $(OBJS)

fclean:
	$(MAKE) clean
	rm -f $(NAME)
re:
	$(MAKE) fclean
	$(MAKE) all

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(LIBFT):
	make -C $(LIBFT_DIR) all

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c -o $@ $?
