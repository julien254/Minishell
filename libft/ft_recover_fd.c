/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recover_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 00:16:55 by julien            #+#    #+#             */
/*   Updated: 2024/08/03 09:11:27 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rm_return_line(char *str)
{
	if (!str)
		return ;
	while (*str != '\n' && *str)
		str++;
	*str = 0;
}

char	**close_fd(int fd)
{
	close(fd);
	return (NULL);
}

char	**ft_recover_fd(char *file)
{
	int		fd;
	char	**fd_2d;
	size_t	i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	fd_2d = malloc(sizeof(char *) * 1);
	if (!fd_2d)
		return (close_fd(fd));
	i = 0;
	fd_2d[i] = get_next_line(fd);
	rm_return_line(fd_2d[i]);
	while (fd_2d[i])
	{
		fd_2d = ft_realloc(fd_2d, sizeof(char *) * (1 + i), sizeof(char *) * \
																(1 + i + 1));
		if (!fd_2d)
			return (close_fd(fd));
		fd_2d[++i] = get_next_line(fd);
		if (fd_2d[i])
			rm_return_line(fd_2d[i]);
	}
	close(fd);
	return (fd_2d);
}
