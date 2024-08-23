/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:59:39 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/21 18:03:44 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	set_file_name_error(char *block, char **file_name, int *i, int error_id)
{
	if (error_id == 1 && (block[*i] == '\0' || block[*i] == '>' || block[*i] == '<'))
	{
		printf("minishell: syntax error near unexpected token `%c'\n", block[*i]);
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

static char	*set_file_name(char *block, int *i)
{
	char	*file_name;
	int		save_i;
	int		j;

	(*i)++;
	if ((block[*i] == '>' && block[*i - 1] == '>')
		|| (block[*i] == '<' && block[*i - 1] == '<'))
		(*i)++;
	while (block[*i] && ft_iswhitespace(block[*i]))
		(*i)++;
	j = *i;
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

char	*rm_redirect(char *block, int j, int i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(block, 0, j);
	tmp2 = ft_substr(block, i, ft_strlen(block) - i);
	tmp3 = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	free(block);
	return (tmp3);
}

static int	file_name_error(char *file_name)
{
	if (!file_name)
		return (1);
	if (file_name[0] == '\0')
	{
		free(file_name);
		return (1);
	}
	return (0);
}

static char	*set_redirect_out(char *block, int *i, int *fd_out, int *error)
{
	char	*file_name;
	int		j;

	j = *i;
	file_name = set_file_name(block, i);
	if (file_name_error(file_name))
		return (NULL);
	(*i)++;
	if (block[*i] == '>')
		*fd_out = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		*fd_out = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd_out == -1)
	{
		printf("minishell: %s: No such file or directory\n", file_name);
		free(file_name);
		*error = 0;
		return (NULL);
	}
	free(file_name);
	block = rm_redirect(block, j, *i - 1);
	*i = j - 1;
	return (block);
}

char	*set_redirect(char *block, int *fd_out, int *fd_in, int *error)
{
	int	i;

	i = 0;
	*fd_in = 5;
	while (block[i])
	{
		i = skip_quotes_while(block, i);
		if (block[i] == '>')
			block = set_redirect_out(block, &i, fd_out, error);
		//else if (block[i] == '<')
			//block = set_redirect_in(block, &i, fd_in);
		if (!block)
			return (NULL);
		i++;
	}
	return (block);
}
