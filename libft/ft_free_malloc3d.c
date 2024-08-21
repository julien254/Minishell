/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_malloc3d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:38:24 by jdetre            #+#    #+#             */
/*   Updated: 2024/07/07 15:40:07 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_free_malloc3d(void ***tab3d)
{
	int	y;
	int	x;

	if (!tab3d)
		return (NULL);
	y = 0;
	while (tab3d[y])
	{
		x = 0;
		while (tab3d[y][x])
		{
			free(tab3d[y][x]);
			x++;
		}
		free(tab3d[y]);
		y++;
	}
	free(tab3d);
	return (NULL);
}
