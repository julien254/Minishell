/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:28:47 by judetre           #+#    #+#             */
/*   Updated: 2024/02/26 16:29:35 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	check_overlap(void *dest, const void *src, size_t n)
{
	if (dest > src && dest <= src + n)
		return (1);
	else
		return (0);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (src == NULL)
		return (NULL);
	if (check_overlap(dest, src, n))
	{
		i = n;
		while (i-- != 0)
			*(char *)(dest + i) = *(char *)(src + i);
	}
	else
	{
		i = 0;
		while (i < n)
		{
			*(char *)(dest + i) = *(char *)(src + i);
			i++;
		}
	}
	return (dest);
}
