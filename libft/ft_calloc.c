/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:45:31 by judetre           #+#    #+#             */
/*   Updated: 2023/11/03 17:32:46 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void				*ptr;
	unsigned long long	siz;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (((long long)nmemb) < 0 || ((long long)size) < 0)
		return (NULL);
	siz = nmemb * size;
	if (siz > SIZE_MAX)
		return (NULL);
	ptr = malloc(siz);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, siz);
	return (ptr);
}
