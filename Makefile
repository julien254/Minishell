# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/30 16:35:18 by jdetre            #+#    #+#              #
#    Updated: 2024/08/21 18:04:17 by gcannaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

NAME_BONUS	=	

CC			=	clang

CFLAGS		=	-Wall -Wextra -Werror -g -lreadline -Wno-unused-command-line-argument

INCLUDE		=	-I./include

LIB			=	-L${LIBPATH} -lft

SRCS		=	src/minishell.c										\
				src/env/recover_env.c								\
				src/lst_management/lst_env_utils.c					\
				src/utils/signal.c									\
				src/utils/ft_free_tab.c								\
				src/utils/ft_iswhitespace.c							\
				src/parsing/parsing.c								\
				src/parsing/command_split.c							\
				src/parsing/lst_parse_management/lst_pars_utils.c	\
				src/parsing/quote/quote_split.c

SRCS_BONUS	=	

OBJS		= 	${SRCS:.c=.o}

OBJS_BONUS	= 	${SRCS_BONUS:.c=.o}

LIBPATH		= 	libft/

all:			${NAME}

${NAME}:		${OBJS}
			make -C ${LIBPATH}
			${CC} ${CFLAGS} $^ ${INCLUDE} ${LIB} -o $@

bonus:			${NAME_BONUS}

${NAME_BONUS}:	${OBJS_BONUS}
			make -C ${LIBPATH}
			${CC} ${CFLAGS} $^ ${INCLUDE} ${LIB} -o ${NAME_BONUS}

clean:
			make clean -C ${LIBPATH}
			rm -f ${OBJS} ${OBJS_BONUS}

fclean:			clean
			make fclean -C ${LIBPATH}
			rm -f ${NAME} ${NAME_BONUS}

re:				fclean all

.PHONY:			all clean fclean re
