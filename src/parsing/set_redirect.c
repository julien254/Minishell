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

static char	*set_redirect_in(char *block, int *i, t_set_fd *set_fd, int *error)
{
	char	*file_name;
	int		j;

	j = *i;
	file_name = set_file_name(block, i, error);
	file_name = handle_file_name_error(file_name, block, set_fd);
	if (!file_name)
		return (NULL);
	if (set_fd->fd_in > 0 && set_fd->fd_in_name)
		close(set_fd->fd_in);
	if (set_fd->fd_out != -1 && set_fd->fd_in != -1)
		set_fd->fd_in = open(file_name, O_RDONLY);
	if (set_fd->fd_in_name)
		free(set_fd->fd_in_name);
	set_fd->fd_in_name = file_name;
	block = rm_redirect(block, j, *i, &set_fd->error);
	*i = j - 1;
	return (block);
}

static void	set_fd_out(t_set_fd *set_fd, char *file_name, int flags)
{
	if (set_fd->fd_out > 0 && set_fd->fd_out_name)
		close(set_fd->fd_out);
	set_fd->fd_out = open(file_name, flags, 0644);
	if (set_fd->fd_out_name)
		free(set_fd->fd_out_name);
	set_fd->fd_out_name = file_name;
}

static char	*set_redirect_out(char *block, int *i, t_set_fd *set_fd, int *error)
{
	char	*file_name;
	int		j;

	j = *i;
	file_name = set_file_name(block, i, error);
	file_name = handle_file_name_error(file_name, block, set_fd);
	if (!file_name)
		return (NULL);
	(*i)++;
	if (block[j + 1] == '>' && (set_fd->fd_out != -1 && set_fd->fd_in != -1))
		set_fd_out(set_fd, file_name, O_CREAT | O_RDWR | O_APPEND);
	else if (set_fd->fd_out != -1 && set_fd->fd_in != -1)
		set_fd_out(set_fd, file_name, O_CREAT | O_WRONLY | O_TRUNC);
	else
		free(file_name);
	block = rm_redirect(block, j, *i - 1, &set_fd->error);
	*i = j - 1;
	return (block);
}

static void	init_set_fd(t_set_fd *set_fd)
{
	set_fd->heredoc_index = 0;
	set_fd->heredoc_name = NULL;
	set_fd->fd_in_name = NULL;
	set_fd->fd_out_name = NULL;
}

char	*set_redirect(t_minishell *shell, char *block, t_set_fd *set_fd)
{
	int	i;

	i = 0;
	init_set_fd(set_fd);
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
		if (block && block[0] == 0)
			break ;
		if (!block || block[0] == 0)
			return (NULL);
		i++;
	}
	return (block);
}
