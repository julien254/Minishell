/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 12:47:58 by julien            #+#    #+#             */
/*   Updated: 2022/05/28 10:34:46 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int				i;
	unsigned int	nb;

	i = 0;
	if (n < 0)
	{
		i += ft_putchar_fd('-', fd);
		nb = n * -1;
	}
	else
		nb = n;
	if (nb <= 9)
		i += ft_putchar_fd('0' + nb, fd);
	else
	{
		i += ft_putnbr_fd(nb / 10, fd);
		i += ft_putchar_fd('0' + nb % 10, fd);
	}
	return (i);
}
