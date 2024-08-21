/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab3d_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:27:51 by jdetre            #+#    #+#             */
/*   Updated: 2024/07/11 12:36:50 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	***malloc_axis_z(int ***tab3d, int size_x, int size_z, int y)
{
	int	x;

	x = 0;
	while (x < size_x)
	{
		tab3d[y][x] = (int *)malloc(sizeof(int) * size_z);
		if (!tab3d[y][x])
		{
			tab3d[y + 1] = NULL;
			ft_free_malloc3d((void *)tab3d);
			return (NULL);
		}
		x++;
	}
	tab3d[y][x] = NULL;
	return (tab3d);
}

int	***ft_tab3d_int(int size_y, int size_x, int size_z)
{
	int	y;
	int	***tab3d;

	tab3d = (int ***)malloc(sizeof(int **) * (size_y + 1));
	if (!tab3d)
		return (NULL);
	y = 0;
	while (y < size_y)
	{
		tab3d[y] = (int **)malloc(sizeof(int *) * (size_x + 1));
		if (!tab3d[y])
		{
			ft_free_malloc3d((void *)tab3d);
			return (NULL);
		}
		tab3d = malloc_axis_z(tab3d, size_x, size_z, y);
		if (!tab3d)
			return (NULL);
		y++;
	}
	tab3d[y] = NULL;
	return (tab3d);
}
