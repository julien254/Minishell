/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab2d_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:27:51 by jdetre            #+#    #+#             */
/*   Updated: 2024/07/07 15:44:05 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	**ft_tab2d_int(int size_y, int size_x)
{
	int	y;
	int	**tab2d;

	tab2d = (int **)malloc(sizeof(int *) * size_y + 1);
	if (!tab2d)
		return (NULL);
	y = 0;
	while (y < size_y)
	{
		tab2d[y] = (int *)malloc(sizeof(int) * size_x);
		if (!tab2d[y])
		{
			ft_free_malloc2d((void *)tab2d);
			return (NULL);
		}
		y++;
	}
	tab2d[y] = NULL;
	return (tab2d);
}
