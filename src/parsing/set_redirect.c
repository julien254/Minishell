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

static char	*rm_redirect(char *block, int j, int i)
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

static char	*set_redirect_in(char *block, int *i, int *fd_in)
{
	char	*file_name;
	int		j;

	j = *i;
	file_name = set_file_name(block, i);
	if (file_name_error(file_name))
		return (NULL);
	*fd_in = open(file_name, O_RDONLY);
	if (*fd_in == -1)
	{
		printf("minishell: %s: No such file or directory\n", file_name);
		free(file_name);
		return (NULL);
	}
	free(file_name);
	block = rm_redirect(block, j, *i);
	*i = j - 1;
	return (block);
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
		else if (block[i] == '<')
			block = set_redirect_in(block, &i, fd_in);
		if (!block)
			return (NULL);
		i++;
	}
	return (block);
}
