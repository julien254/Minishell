/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:59:39 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/21 18:03:44 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../include/minishell.h"

static size_t	ft_count_words(char *s)
{
	size_t	words;
	size_t	i;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"'
			|| s[i] == '\'')
			i = skip_quotes(s, i);
		if ((ft_iswhitespace(s[i + 1]) || s[i + 1] == '\0')
			&& !ft_iswhitespace(s[i]))
			words++;
		i++;
	}
	return (words);
}

char	**quote_split(char *s)
{
	char	**tab;
	size_t	j;

	if (s == NULL)
		return (NULL);
	tab = ft_calloc((ft_count_words(s) + 1), sizeof(char *));
	if (tab == NULL)
		return (NULL);
	j = 0;
	while (*s != '\0')
	{
		if (ft_iswhitespace(*s))
			s++;
		else
			s += split_word(&s, tab, j++);
	}
	tab[j] = 0;
	return (tab);
}
