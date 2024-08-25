/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_at_first_pattern.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 08:06:27 by judetre           #+#    #+#             */
/*   Updated: 2024/08/25 08:43:47 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
int	if_no_pattern(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	if (!str[i])
		return (1);
	return (0);

}

static char	**ft_split_no_pattern(char *str)
{
	char	**split;
	int		i;

	i = 0;
	while (str[i])
		i++;
	split = (char **)malloc(sizeof(char *) * 2);
	if (!split)
		return (NULL);
	split[0] = (char *)malloc(sizeof(char) * i + 1);
	if (!split[0])
		return (NULL);
	ft_strlcpy(split[0], str, i + 1);
	split[1] = NULL;
	return (split);
}

char	**ft_split_at_first_pattern(char *str, char c)
{
	char	**split;
	int		size_first_str;
	int		size_last_str;
	int		i;

	size_last_str = 1;
	i = 0;
	if (if_no_pattern(str, c))
		return (ft_split_no_pattern(str));
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
