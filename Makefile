# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 19:07:21 by eoddish           #+#    #+#              #
#    Updated: 2022/02/21 17:56:03 by eoddish          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ircserv

SRCS		= main.cpp Server.cpp ErrorMess.cpp commands/RegistrUser.cpp User.cpp Message.cpp CmdMess.cpp commands/SendingMessage.cpp Utills.cpp Channel.cpp commands/ChannelOper.cpp

OBJS		= $(SRCS:.cpp=.o)

CC			= clang++

CFLAGS		= -Wall -Wextra -Werror -std=c++98

%.o: %.cpp Makefile Server.hpp ErrorMess.hpp User.hpp Message.hpp CmdMess.hpp
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
