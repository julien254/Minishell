/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_u_nbr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 12:47:58 by julien            #+#    #+#             */
/*   Updated: 2022/05/28 07:48:04 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_u_nbr_fd(unsigned int n, int fd)
{
	int	i;

	i = 0;
	if (n <= 9)
		i += ft_putchar_fd('0' + n, fd);
	else
	{
		i += ft_putnbr_fd(n / 10, fd);
		i += ft_putchar_fd('0' + n % 10, fd);
	}
	return (i);
}
