/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy_tab2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:25:21 by julien            #+#    #+#             */
/*   Updated: 2022/10/09 06:26:49 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_cpy_tab2d(char **tab2d)
{
	char	**tab2d_cpy;
	size_t	nbr_line;
	size_t	i;

	nbr_line = ft_tab2dlen(tab2d);
	tab2d_cpy = (char **)calloc(sizeof(char *) * nbr_line + 1, 0);
	tab2d_cpy[nbr_line] = 0;
	i = 0;
	while (i < nbr_line)
	{
		tab2d_cpy[i] = (char *)calloc(ft_strlen(tab2d[i]) + 1, 0);
		ft_strlcpy(tab2d_cpy[i], tab2d[i], ft_strlen(tab2d[i]) + 1);
		i++;
	}
	return (tab2d_cpy);
}
