/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 10:24:02 by jdetre            #+#    #+#             */
/*   Updated: 2024/02/10 07:32:21 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	set_struct_save(int fd, t_save *save)
{
	int	i;

	i = 0;
	while (fd != save->fd[i] && save->fd[i] != 0)
		i++;
	if (save->fd[i] == 0)
		save->fd[i] = fd;
	if (i == 0)
	{
		while (i < 200)
			save->read_size[i++] = 1;
		i = 0;
	}
	return (i);
}

static char	*ft_realloc_gnl(char *buffer, int multiplier, t_save *save, \
														int current_fd)
{
	char	*new_buffer;

	new_buffer = (char *)malloc((BUFFER_SIZE * multiplier) + \
			save->size_residue[current_fd] + 1);
	if (!new_buffer)
		return (NULL);
	new_buffer[0] = 0;
	if (save->residue[current_fd] != NULL)
	{
		ft_strlcat_gnl(new_buffer, save->residue[current_fd]);
		free(save->residue[current_fd]);
	}
	if (buffer)
	{
		ft_strlcat_gnl(new_buffer, buffer);
		free(buffer);
	}
	return (new_buffer);
}

char	*read_while_noendline(int fd, t_save *save, int current_fd)
{
	char	*buffer;
	char	*buffer_tmp;
	size_t	multiplier;

	multiplier = 0;
	buffer_tmp = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer_tmp)
		return (NULL);
	buffer_tmp[0] = 0;
	buffer = 0;
	while (if_is_endline_gnl(buffer_tmp) != 1 && save->read_size[current_fd] \
			!= 0)
	{
		multiplier++;
		buffer = ft_realloc_gnl(buffer, multiplier, save, current_fd);
		if (multiplier == 1)
			save->residue[current_fd] = NULL;
		save->read_size[current_fd] = read(fd, buffer_tmp, BUFFER_SIZE);
		if (save->read_size[current_fd] <= 0)
			return (free_all_gnl(buffer_tmp, buffer));
		buffer_tmp[save->read_size[current_fd]] = 0;
		ft_strlcat_gnl(buffer, buffer_tmp);
	}
	free(buffer_tmp);
	return (buffer);
}

char	*get_residue(char *line)
{
	int		i;
	char	*residue;

	i = 0;
	while (line[i] != '\n' && line[i] != 0)
		i++;
	if (line[i] == '\0' || ((line[i] == '\n') && (line[i + 1] == '\0')))
		return (NULL);
	residue = (char *)malloc((ft_strlen(line) - i));
	if (!residue)
		return (NULL);
	residue[0] = '\0';
	ft_strlcat_gnl(residue, line + i + 1);
	line[i + 1] = '\0';
	return (residue);
}

char	*get_next_line(int fd)
{
	static t_save	save;
	char			*line;
	int				current_fd;

	current_fd = set_struct_save(fd, &save);
	save.size_residue[current_fd] = ft_strlen(save.residue[current_fd]);
	if (save.residue[current_fd] && if_is_endline_gnl(save.residue[current_fd]))
	{
		line = ft_strdup(save.residue[current_fd]);
		free(save.residue[current_fd]);
		save.residue[current_fd] = get_residue(line);
		return (line);
	}
	line = read_while_noendline(fd, &save, current_fd);
	if (line == NULL)
		return (NULL);
	save.residue[current_fd] = get_residue(line);
	if (save.read_size[current_fd] <= 0 && line[0] == 0)
		line = free_all_gnl(line, save.residue[current_fd]);
	return (line);
}
