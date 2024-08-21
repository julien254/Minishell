/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:51:43 by judetre           #+#    #+#             */
/*   Updated: 2023/11/01 14:29:04 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (src == NULL || dest == NULL)
		return (dest);
	i = -1;
	while (++i < n)
		*(char *)(dest + i) = *(char *)(src + i);
	return (dest);
}
