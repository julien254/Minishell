/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:43:00 by judetre           #+#    #+#             */
/*   Updated: 2023/11/06 11:40:43 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

static size_t	size(int n)
{
	size_t	i;
	size_t	nb;

	if (n == -2147483648)
		nb = 2147483648;
	else if (n < 0)
		nb = -n;
	else
		nb = n;
	i = 1;
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

static void	strrev(char *str)
{
	size_t	i;
	size_t	size;
	char	tmp;

	size = ft_strlen(str);
	i = 0;
	while (i < size / 2)
	{
		tmp = str[i];
		str[i] = str[size - i - 1];
		str[size - i++ - 1] = tmp;
	}
}

char	*ft_itoa(int n)
{
	char		*nbr;
	int			isneg;
	size_t		i;

	isneg = (n < 0);
	nbr = malloc(size(n) + 1 + isneg);
	if (!nbr)
		return (NULL);
	ft_bzero(nbr, size(n) + 1 + isneg);
	if (n == 0)
		nbr[0] = '0';
	i = 0;
	while (n != 0)
	{
		nbr[i++] = '0' + ft_abs(n % 10);
		n = n / 10;
	}
	if (isneg)
		nbr[i] = '-';
	strrev(nbr);
	return (nbr);
}
