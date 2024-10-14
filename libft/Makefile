# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/25 23:42:02 by jdetre            #+#    #+#              #
#    Updated: 2024/10/14 11:12:57 by jdetre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC			= clang

CFLAGS		= -Wall -Wextra -Werror -I. -g

SRCS		=	ft_atoi.c							\
				ft_bzero.c							\
				ft_calloc.c							\
				ft_isalnum.c						\
				ft_isalpha.c						\
				ft_isascii.c						\
				ft_isdigit.c						\
				ft_isprint.c						\
				ft_is_white_space.c					\
				ft_itoa.c							\
				ft_memchr.c							\
				ft_memcmp.c							\
				ft_memcpy.c							\
				ft_memmove.c    					\
				ft_memset.c     					\
				ft_putchar_fd.c 					\
				ft_putendl_fd.c 					\
				ft_putnbr_fd.c  					\
				ft_putstr_fd.c  					\
				ft_split.c      					\
				ft_split_at_first_pattern.c      	\
				ft_strchr.c     					\
				ft_strdup.c     					\
				ft_striteri.c   					\
				ft_strjoin.c    					\
				ft_strlcat.c    					\
				ft_strlcpy.c    					\
				ft_strlen.c     					\
				ft_strmapi.c    					\
				ft_strncmp.c    					\
				ft_strcmp.c 	   					\
				ft_strnstr.c    					\
				ft_strrchr.c    					\
				ft_strtrim.c    					\
				ft_substr.c     					\
				ft_tolower.c    					\
				ft_toupper.c						\
				ft_count_line.c						\
				ft_cpy_tab2d.c						\
				ft_line_size.c						\
				ft_line_size_max.c					\
				ft_putadd_fd.c						\
				ft_puthexa_fd.c						\
				ft_puthexa_ll_fd.c					\
				ft_puttab2_fd.c						\
				ft_put_u_nbr_fd.c					\
				ft_recover_fd.c						\
				ft_strjoin_malloc.c					\
				ft_tab2dlen.c						\
				ft_lstadd_back.c 					\
				ft_lstadd_front.c					\
				ft_lstclear.c    					\
				ft_lstdelone.c   					\
				ft_lstiter.c     					\
				ft_lstlast.c     					\
				ft_lstmap.c      					\
				ft_lstnew.c      					\
				ft_lstsize.c     					\
				ft_realloc.c						\
				ft_free_malloc2d.c  				\
				ft_tab2d_int.c						\
				ft_free_malloc3d.c  				\
				ft_tab3d_int.c						\
				ft_print_bits.c						\
				ft_printf.c							\
				get_next_line.c						\
				get_next_line_utils.c

OBJS		= ${SRCS:.c=.o}


all:		${NAME}

${NAME}:	${OBJS}
	ar rcs ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}

fclean:		clean
	rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
