/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_malloc2d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:01:32 by judetre           #+#    #+#             */
/*   Updated: 2024/07/31 13:11:34 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_free_malloc2d(void **tab2d)
{
	int	i;

	if (!tab2d)
		return (NULL);
	i = 0;
	while (tab2d[i])
	{
		free(tab2d[i]);
		i++;
	}
	free(tab2d);
	return (NULL);
}
