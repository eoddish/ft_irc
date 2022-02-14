# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eoddish <eoddish@student.21-school>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 19:07:21 by eoddish           #+#    #+#              #
#    Updated: 2022/02/14 16:00:33 by eoddish          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ircserv

SRCS		= main.cpp Server.cpp ErrorMess.cpp RegistrUser.cpp User.cpp Message.cpp

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
