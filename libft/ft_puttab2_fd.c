/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab2_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 08:58:12 by julien            #+#    #+#             */
/*   Updated: 2024/02/10 08:07:06 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puttab2_fd(char **tab, int fd)
{
	int	i;
	int	count;

	if (!tab || !tab[0])
		return (0);
	i = 0;
	count = 0;
	while (tab[i])
		count += ft_putendl_fd(tab[i++], fd);
	count += ft_putendl_fd(tab[i], fd);
	return (count);
}
