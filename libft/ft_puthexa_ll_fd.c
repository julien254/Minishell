/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_ll_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 08:03:24 by jdetre            #+#    #+#             */
/*   Updated: 2022/05/31 14:49:58 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_puthexa_ll_fd(size_t nbr, int fd, int uppercase)
{
	int		i;
	char	*basehexa;

	i = 0;
	if (uppercase)
		basehexa = "0123456789ABCDEF";
	else
		basehexa = "0123456789abcdef";
	if (nbr < 16)
		i += ft_putchar_fd(basehexa[nbr], fd);
	else
	{
		i += ft_puthexa_ll_fd(nbr / 16, fd, uppercase);
		i += ft_putchar_fd(basehexa[nbr % 16], fd);
	}
	return (i);
}
