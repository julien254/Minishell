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
static char	*ft_set_tmp(char *tmp, char *str, int i, int j)
{
	char	*tmp2;
	char	*tmp3;

	tmp2 = NULL;
	tmp3 = NULL;
	tmp2 = ft_substr(str, j + 1, (i - 1) - j);
	tmp3 = ft_substr(str, i + 1, (ft_strlen(str) - i));
	i--;
	str = ft_strjoin(ft_strjoin(tmp, tmp2), tmp3);
	free(tmp);
	free(tmp2);
	free(tmp3);
	return (str);
}

static int	ft_quote_skip_char(char *a_line, int i)
{
	char	c;
	int		s;

	s = i;
	c = a_line[i];
	i++;
	while (a_line[i] != 0 && a_line[i] != c)
		i++;
	if (a_line[i] == 0)
		return (s);
	return (i);
}

static char	*handle_quote_aply_str(char *str, int *i, int *j)
{
	char	*tmp;

	tmp = ft_substr(str, 0, *i);
	*j = *i;
	*i = ft_quote_skip_char(str, *i);
	if (*i != *j)
	{
		str = ft_set_tmp(tmp, str, *i, *j);
		(*i)--;
	}
	else
	{
		free(tmp);
		*i = *j;
	}
	return (str);
}

static char	*ft_skip_quot_in_str(char *str, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
			str = handle_quote_aply_str(str, &i, &j);
		else
			i++;
	}
	return (str);
}

static size_t	handle_quotes(char **s, size_t i)
{
	size_t	tmp;
	size_t	k;

	tmp = i;
	k = 0;
	while ((*s)[i] == '"' || (*s)[i] == '\'')
	{
		i = ft_quote_skip_char(*s, i) + 1;
		k += 2;
	}
	i -= k;
	*s = ft_skip_quot_in_str(*s, (*s)[tmp]);
	return (i);
}

static size_t	ft_count_words(char *s, char c)
{
	size_t	words;
	size_t	i;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"'
			|| s[i] == '\'')
			i = ft_quote_skip_char(s, i);
		if ((s[i + 1] == c || s[i + 1] == '\0') && s[i] != c)
			words++;
		i++;
	}
	return (words);
}

static char	*ft_substr_split(char *s, unsigned int st, size_t l, char **t)
{
	size_t			i;
	size_t			len_m;
	char			*str;

	if (!s)
		return (NULL);
	len_m = ft_strlen(s) - st;
	if (len_m >= l)
		len_m = l;
	if (st > ft_strlen(s))
		len_m = 0;
	str = ft_calloc(len_m + 1, sizeof(char));
	if (str == NULL)
	{
		ft_free_tab(t);
		return (NULL);
	}
	i = 0;
	while (i < len_m)
		str[i++] = s[st++];
	str[i] = '\0';
	return (str);
}

static size_t	split_word(char **s, char c, char **tab, size_t j)
{
	size_t	i;

	i = 0;
	while ((*s)[i] != c && (*s)[i] != '\0')
	{
		if (((*s)[i] == '"' || (*s)[i] == '\'') && (*s)[i + 1] != 0)
			i = handle_quotes(s, i);
		else
			i++;
	}
	tab[j] = ft_substr_split(*s, 0, i, tab);
	return (i);
}

char	**quote_split(char *s, char c)
{
	char	**tab;
	size_t	j;

	if (s == NULL)
		return (NULL);
	tab = ft_calloc((ft_count_words(s, c) + 1), sizeof(char *));
	if (tab == NULL)
		return (NULL);
	j = 0;
	while (*s != '\0')
	{
		if (*s == c)
			s++;
		else
			s += split_word(&s, c, tab, j++);
	}
	tab[j] = 0;
	return (tab);
}
