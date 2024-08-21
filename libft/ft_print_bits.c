/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:34:54 by jdetre            #+#    #+#             */
/*   Updated: 2024/07/28 13:48:16 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	calculate_bits_needed(long int num)
{
	int	count;

	if (num == 0)
		return (1);
	count = 0;
	while (num > 0)
	{
		num >>= 1;
		count++;
	}
	return (count);
}

char	*ft_print_bits(long int nbr)
{
	int		bits;
	char	*binary;
	int		index;

	bits = calculate_bits_needed(nbr);
	binary = (char *)malloc(bits + 1);
	if (binary == NULL)
	{
		perror("Error allocate memory");
		return (NULL);
	}
	binary[bits] = '\0';
	index = bits - 1;
	while (index >= 0)
	{
		if (nbr & 1)
			binary[index] = '1';
		else
			binary[index] = '0';
		nbr >>= 1;
		index--;
	}
	return (binary);
}
