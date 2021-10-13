# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngeschwi <nathan.geschwind@gmail.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/02 10:53:12 by ngeschwi          #+#    #+#              #
#    Updated: 2021/10/14 00:33:38 by ngeschwi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c \
		sources/ft_life.c \
		sources/ft_print.c \
		sources/ft_error.c \
		sources/utils/ft_atoi.c

OBJS	= $(SRCS:.c=.o)

OBJ_PATH := objets

PATH_OBJS := $(addprefix $(OBJ_PATH)/, $(OBJS))

NAME	= philo

CC		= gcc
RM		= rm -rf
CFLAGS	=  -g -g3  -Wall -Werror -Wextra #-fsanitize=address
LIBS	= -lpthread
LINK	= -Iincludes

all:	$(NAME)

%.o : %.c | $(OBJ_PATH)
	${CC} ${CFLAGS} ${LINK} -c $< -o objets/$@

$(NAME):	$(OBJS)
	${CC} ${CFLAGS} ${PATH_OBJS} ${LINK} ${LIBS} -o ${NAME}

$(OBJ_PATH) :
		mkdir -p objets
		mkdir -p objets/sources
		mkdir -p objets/sources/utils

$(OBJS):	includes/philo.h

clean:
		$(RM) $(PATH_OBJS)

fclean:		clean
		$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re