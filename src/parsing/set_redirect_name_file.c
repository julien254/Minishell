/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect_name_file.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:57:27 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/21 15:56:05 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static int	set_file_name_error(char *block, char **file_name, int *i,
	int error_id)
{
	if ((error_id != 1 && !*file_name)
		|| (error_id == 1 && (block[*i] == '\0' || block[*i] == '>'
				|| block[*i] == '<'))
		|| (error_id == 2 && (*file_name[0] == ft_strcmp(*file_name, "")))
		|| (error_id == 3 && (*file_name[0] == '\0')))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		if (*file_name)
			free(*file_name);
		*file_name = ft_strdup("");
		return (1);
	}
	return (0);
}

static void	skipe_to_name(char *block, int *i, int *j)
{
	(*i)++;
	if ((block[*i] == '>' && block[*i - 1] == '>')
		|| (block[*i] == '<' && block[*i - 1] == '<'))
		(*i)++;
	while (block[*i] && ft_iswhitespace(block[*i]))
		(*i)++;
	*j = *i;
}

static char	*quote_file_name(char *str)

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

char	*set_file_name(char *block, int *i, int *error)
{
	char	*file_name;
	int		j;

	file_name = NULL;
	skipe_to_name(block, i, &j);
	if (!set_file_name_error(block, &file_name, i, 1))
	{
		while (block[*i] && !ft_iswhitespace(block[*i]) && block[*i]
			!= '>' && block[*i] != '<')
		{
			if (block[*i] == '\'' || block[*i] == '"')
				*i = skip_quotes_while(block, *i);
			else
				(*i)++;
		}
		file_name = ft_substr(block, j, *i - j);
		if (file_name && !set_file_name_error(block, &file_name, i, 2))
			file_name = quote_file_name(file_name);
		if (set_file_name_error(block, &file_name, i, 3))
			*error = 2;
	}
	else
		*error = 2;
	return (file_name);
}
