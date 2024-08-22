/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_at_first_pattern.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 08:06:27 by judetre           #+#    #+#             */
/*   Updated: 2024/08/22 06:27:04 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	**ft_split_at_first_pattern(char *str, char c)
{
	char	**split;
	int		size_first_str;
	int		size_last_str;
	int		i;

	size_last_str = 1;
	i = 0;
	while (str[i] != c)
		i++;
	size_first_str = i++;
	while (str[++i])
		size_last_str++;
	split = (char **)malloc(sizeof(char *) * 3);
	if (!split)
		return (NULL);
	split[0] = (char *)malloc(sizeof(char) * size_first_str + 1);
	split[1] = (char *)malloc(sizeof(char) * size_last_str + 1);
	split[2] = NULL;
	if (!split[0] || !split[1])
		return (NULL);
	ft_strlcpy(split[0], str, size_first_str + 1);
	ft_strlcpy(split[1], str + size_first_str + 1, size_last_str + 1);
	return (split);
}
