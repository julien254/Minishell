/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:29:41 by judetre           #+#    #+#             */
/*   Updated: 2023/11/03 17:33:28 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;
	size_t	srclen;

	if (!dst)
		return (0);
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = dstlen;
	if (dstlen < size - 1 && size > 0)
	{
		j = 0;
		while (i < size - 1 && src[j])
			dst[i++] = src[j++];
		dst[i] = '\0';
	}
	if (dstlen > size)
		dstlen = size;
	return (srclen + dstlen);
}
