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
	if (error_id != 1 && !*file_name)
		return (1);
	if (error_id == 1 && (block[*i] == '\0' || block[*i] == '>'
			|| block[*i] == '<'))
	{
		printf("minishell: syntax error near unexpected token `%c'\n",
			block[*i]);
		*file_name = ft_strdup("");
		return (1);
	}
	if (error_id == 2 && (*file_name[0] == ft_strcmp(*file_name, """")))
	{
		printf("minishell: %s: No such file or directory\n", *file_name);
		free(*file_name);
		*file_name = ft_strdup("");
		return (1);
	}
	if (error_id == 3 && (*file_name[0] == '\0'))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
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

char	*set_file_name(char *block, int *i)
{
	char	*file_name;
	int		save_i;
	int		j;

	skipe_to_name(block, i, &j);
	if (set_file_name_error(block, &file_name, i, 1))
		return (file_name);
	while (block[*i] && !ft_iswhitespace(block[*i]) && block[*i] != '>'
		&& block[*i] != '<')
	{
		if (block[*i] == '\'' || block[*i] == '"')
			*i = skip_quotes_while(block, *i);
		else
			(*i)++;
	}
	save_i = *i;
	file_name = ft_substr(block, j, save_i - j);
	if (!file_name)
		return (NULL);
	if (set_file_name_error(block, &file_name, i, 2))
		return (file_name);
	file_name = str_remove_quotes(file_name);
	if (set_file_name_error(block, &file_name, i, 3))
		return (file_name);
	return (file_name);
}
