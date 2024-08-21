/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:56:10 by jdetre            #+#    #+#             */
/*   Updated: 2024/02/25 14:02:33 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	count_word(const char *str, char sep)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (str[i++] != sep)
		count++;
	while (str[i])
	{
		if (str[i] != sep && str[i - 1] == sep)
			count++;
		i++;
	}
	return (count);
}

char	*substr(const char *str, int start, int end)
{
	int		size;
	char	*substr;
	int		i;

	size = (end - start) + 1;
	substr = (char *)malloc((size + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		substr[i] = str[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}

char	**ft_split(const char *s, char c)
{
	int		start;
	int		i[2];
	char	**split;

	split = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!split)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (s[i[0]])
	{
		if (s[i[0]] != c)
		{
			start = i[0];
			while (s[i[0]] != c && s[i[0]])
				i[0]++;
			split[i[1]++] = substr(s, start, i[0] - 1);
			if (!split[i[1] - 1])
				return ((char **)ft_free_malloc2d((void **)split));
		}
		else
			i[0]++;
	}
	split[i[1]] = NULL;
	return (split);
}
