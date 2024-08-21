/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 08:34:43 by jdetre            #+#    #+#             */
/*   Updated: 2022/05/31 14:49:26 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putadd_fd(size_t hexa, int fd)
{
	int	i;

	i = 0;
	if (!hexa)
		return (write(fd, "(nil)", 5));
	ft_putstr_fd("0x", fd);
	i += ft_puthexa_ll_fd(hexa, fd, 0);
	return (i + 2);
}
