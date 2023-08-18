# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/17 20:52:41 by minjeon2          #+#    #+#              #
#    Updated: 2023/08/18 20:10:12 by minjeon2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRCS = main.c utils.c acting.c philo_monitor.c list_maker.c memory_manager.c
OBJS = $(SRCS:.c=.o)

.PHONY : clean fclean re all

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean:
	$(MAKE) clean
	rm -f $(NAME)
re:
	$(MAKE) fclean
	$(MAKE) all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $?
