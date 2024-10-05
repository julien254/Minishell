/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:59:39 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/21 18:03:44 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	skip_quotes_error(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	if (str[i] == 0)
		return (0);
	while (str[i] && str[i] != quote && str[i] != 0)
		i++;
	if (str[i] == 0)
		return (0);
	return (i);
}

int	quote_error(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			i = skip_quotes_error(s, i);
			if (i == 0)
				return (1);
		}
		if (s[i] == '|' && s[i + 1] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	skip_quotes(char *str, int i)
{
	char	quote;
	int		save_i;

	quote = str[i];
	i++;
	if (str[i] == 0)
		return (i);
	save_i = i;
	while (str[i] && str[i] != quote && str[i] != 0)
		i++;
	if (str[i] == 0)
		return (save_i);
	return (i);
}

int	skip_quotes_while(char *str, int i)
{
	while (str[i] && (str[i] == '"' || str[i] == '\''))
		i = skip_quotes(str, i);
	return (i);
}

char	*str_remove_quotes(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			remove_quotes(&str, &i);
		else
			i++;
	}
	return (str);
}
