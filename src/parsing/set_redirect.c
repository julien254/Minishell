/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:59:39 by gcannaud          #+#    #+#             */
/*   Updated: 2024/10/14 12:21:06 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

char	*rm_redirect(char *block, int j, int i, int *error)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(block, 0, j);
	tmp2 = ft_substr(block, i, ft_strlen(block) - i);
	tmp3 = ft_strjoin(tmp, tmp2);
	if (!tmp3)
	{
		if (tmp)
			free(tmp);
		if (tmp2)
			free(tmp2);
		*error = 1;
		return (NULL);
	}
	free(tmp);
	free(tmp2);
	free(block);
	return (tmp3);
}

int	file_name_error(char *file_name, int *error)
{
	if (!file_name)
	{
		*error = 1;
		return (1);
	}
	if (file_name[0] == '\0')
	{
		free(file_name);
		return (1);
	}
	return (0);
}

static char	*set_redirect_in(char *block, int *i, t_set_fd *set_fd, int *error)
{
	char	*file_name;
	int		j;

	j = *i;
	file_name = set_file_name(block, i, error);
	if (file_name_error(file_name, &set_fd->error))
		return (NULL);
	if (set_fd->fd_out != -1 && set_fd->fd_in != -1)
		set_fd->fd_in = open(file_name, O_RDONLY);
	set_fd->fd_in_name = file_name;
	block = rm_redirect(block, j, *i, &set_fd->error);
	*i = j - 1;
	return (block);
}

static char	*set_redirect_out(char *block, int *i, t_set_fd *set_fd, int *error)
{
	char	*file_name;
	int		j;

	j = *i;
	file_name = set_file_name(block, i, error);
	if (file_name_error(file_name, &set_fd->error))
		return (NULL);
	(*i)++;
	if (block[j + 1] == '>' && (set_fd->fd_out != -1 && set_fd->fd_in != -1))
	{
		set_fd->fd_out = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
		set_fd->fd_out_name = file_name;
	}
	else if (set_fd->fd_out != -1 && set_fd->fd_in != -1)
	{
		set_fd->fd_out = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		set_fd->fd_out_name = file_name;
	}
	else
		free(file_name);
	block = rm_redirect(block, j, *i - 1, &set_fd->error);
	*i = j - 1;
	return (block);
}

char	*set_redirect(t_minishell *shell, char *block, t_set_fd *set_fd)
{
	int	i;

	i = 0;
	set_fd->heredoc_index = 0;
	set_fd->heredoc_name = NULL;
	set_fd->fd_in_name = NULL;
	set_fd->fd_out_name = NULL;
	if (!block)
		return (NULL);
	while (block[i])
	{
		i = skip_quotes_while(block, i);
		if (block[i] == 0)
			break ;
		if (block[i] == '>')
			block = set_redirect_out(block, &i, set_fd, &shell->exit_code);
		else if (block[i] == '<' && block[i + 1] != '<')
			block = set_redirect_in(block, &i, set_fd, &shell->exit_code);
		else if (!ft_strncmp(&block[i], "<<", 1))
			block = set_heredoc(shell, set_fd, block, &i);
		if (!block)
			return (NULL);
		i++;
	}
	return (block);
}
