# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/02 10:53:12 by ngeschwi          #+#    #+#              #
#    Updated: 2021/10/02 12:11:27 by ngeschwi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c \
		sources/utils/ft_atoi.c

OBJS	= $(SRCS:.c=.o)

NAME	= philo

CC		= gcc
RM		= rm -rf
LIBS	= -lpthread

all:	$(NAME)

%.o : %.c
	${CC} -I./includes -c $< -o $@

$(NAME):	$(OBJS)
	${CC} ${OBJS} ${LIBS} -o ${NAME}

$(OBJS):	includes/philo.h

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re