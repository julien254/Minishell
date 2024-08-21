/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:48:19 by judetre           #+#    #+#             */
/*   Updated: 2024/08/21 08:37:15 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdio.h>

/****************** Basic Function ****************/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	**ft_split_at_first_pattern(char *str, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *neW);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *neW);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_count_line(char *str);
char	**ft_cpy_tab2d(char **tab2d);
int		ft_line_size(char *str);
int		ft_line_size_max(char *str);
int		ft_putadd_fd(size_t hexa, int fd);
int		ft_puthexa_fd(unsigned int nbr, int fd, int uppercase);
int		ft_puthexa_ll_fd(size_t nbr, int fd, int uppercase);
int		ft_puttab2_fd(char **tab, int fd);
int		ft_put_u_nbr_fd(unsigned int n, int fd);
char	**ft_recover_fd(char *file);
char	*ft_strjoin_malloc(char *s1, char *s2);
int		ft_tab2dlen(char **tab);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	*ft_free_malloc2d(void **tab2d);
int		**ft_tab2d_int(int size_y, int size_x);
void	*ft_free_malloc3d(void ***tab3d);
int		***ft_tab3d_int(int size_y, int size_x, int size_z);
char	*ft_print_bits(long int nbr);

/***************** PRINTF ***************/

typedef struct s_ind
{
	size_t	i;
	size_t	lastindex;
	size_t	count;
	int		ifarg;
}				t_ind;

int		ft_printf(const char *str, ...);

/**************** GET_NEXT_LINE **********/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_save
{
	int		fd[200];
	char	*residue[200];
	int		size_residue[200];
	ssize_t	read_size[200];
}				t_save;

char	*get_next_line(int fd);
int		ft_strlen_gnl(char *str);
void	ft_strlcat_gnl(char *dst, char *src);
int		if_is_endline_gnl(char *str);
char	*ft_strdup_gnl(char *src);
char	*free_all_gnl(char *line, char *residue);
#endif
