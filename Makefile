# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eoddish <eoddish@student.21-school>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 19:07:21 by eoddish           #+#    #+#              #
#    Updated: 2022/02/07 19:42:49 by eoddish          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ircserv

SRCS		= main.cpp Server.cpp

OBJS		= $(SRCS:.cpp=.o)

CC			= clang++

CFLAGS		= -Wall -Wextra -Werror -std=c++98

%.o: %.cpp Makefile 
			$(CC) $(CFLAGS) -c $< -o $@

RM			= rm -f

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all, clean, fclean, re

.SILENT:
