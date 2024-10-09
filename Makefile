# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/30 16:35:18 by jdetre            #+#    #+#              #
#    Updated: 2024/10/09 11:29:25 by gcannaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

NAME_BONUS	=	

CC			=	clang

CFLAGS		=	-Wall -Wextra -Werror -g -gdwarf-4 -lreadline -Wno-unused-command-line-argument

INCLUDE		=	-I./include

LIB			=	-L${LIBPATH} -lft

SRCS		=	src/minishell.c										\
				src/env/recover_env.c								\
				src/env/make_tab_env.c								\
				src/lst_management/lst_env_utils.c					\
				src/lst_management/lst_env_cpy.c					\
				src/lst_management/return_element_env.c				\
				src/lst_management/return_value_env.c				\
				src/lst_management/remove_element_env.c				\
				src/lst_management/sort_list.c						\
				src/lst_management/free_lst_env.c					\
				src/lst_management/lst_env_size.c					\
				src/lst_management/lst_command_size.c				\
				src/utils/signal.c									\
				src/utils/ft_iswhitespace.c							\
				src/utils/ft_strjoin_env.c							\
				src/parsing/parsing.c								\
				src/parsing/command_split.c							\
				src/parsing/lst_parse_management/lst_pars_utils.c	\
				src/parsing/lst_parse_management/lst_pars_clean.c	\
				src/parsing/quote/quote_split.c						\
				src/parsing/quote/quote_utils.c						\
				src/parsing/quote/split_word.c						\
				src/parsing/set_redirect.c							\
				src/parsing/set_redirect_name_file.c				\
				src/parsing/heredoc/set_heredoc.c					\
				src/parsing/heredoc/here_read.c						\
				src/builtins/ft_env.c								\
				src/builtins/ft_export.c							\
				src/builtins/ft_exit.c								\
				src/builtins/ft_unset.c								\
				src/builtins/ft_pwd.c								\
				src/builtins/ft_echo.c								\
				src/builtins/ft_cd.c								\
				src/exec/exec.c										\
				src/handel/replace_handle.c

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
