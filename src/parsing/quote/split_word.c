/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:59:39 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/21 18:03:44 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*ft_substr_split(char *s, unsigned int st, size_t l)
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
		return (NULL);
	i = 0;
	while (i < len_m)
		str[i++] = s[st++];
	str[i] = '\0';
	return (str);
}

static void	remove_char(char **s, size_t i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(*s, 0, i);
	tmp2 = ft_substr(*s, i + 1, ft_strlen(*s) - i);
	tmp3 = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	ft_strlcpy(*s, tmp3, ft_strlen(tmp3) + 1);
	free(tmp3);
}

static void	remove_quotes(char **s, size_t *i)
{
	size_t	j;
	int		k;

	j = *i;
	j = skip_quotes(*s, j);
	if (j == (*i))
		return ;
	k = *i;
	*i = skip_quotes(*s, *i);
	remove_char(s, k);
	remove_char(s, *i - 1);
	*i -= 1;
}

size_t	split_word(char **s, char **tab, size_t j)
{
	size_t	i;

	i = 0;
	while (!ft_iswhitespace((*s)[i]) && (*s)[i] != '\0')
	{
		if ((*s)[i] == '"' || (*s)[i] == '\'')
			remove_quotes(s, &i);
		else
			i++;
	}
	tab[j] = ft_substr_split(*s, 0, i);
	if (tab[j] == NULL)
		return (0);
	return (i);
}
