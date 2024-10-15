/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:59:39 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/21 18:03:44 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../include/minishell.h"
#include <unistd.h>

static int	ft_fillsave(char *content, char *name)
{
	int	fd;

	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
		return (-1);
	ft_putstr_fd(content, fd);
	close(fd);
	return (0);
}

static char	*generate_tmp_name(int heredoc_index)
{
	char	*tmp;
	char	*tmp_name ;

	tmp = ft_itoa(heredoc_index);
	tmp_name = ft_strjoin("/tmp/heredoc", tmp);
	if (tmp)
		free(tmp);
	return (tmp_name);
}

static void	save_content(char *content, int *heredoc_index, int *pipe_fd)
{
	char	*tmp_name;
	int		ret;

	while (1)
	{
		tmp_name = generate_tmp_name(*heredoc_index);
		if (tmp_name == NULL)
		{
			free(content);
			exit(1);
		}
		ret = ft_fillsave(content, tmp_name);
		if (ret == 0)
			break ;
		free(tmp_name);
		heredoc_index++;
	}
	write(pipe_fd[1], heredoc_index, sizeof(int));
	close(pipe_fd[1]);
	free(tmp_name);
	free(content);
	exit(130);
}

void	write_in_term_sav(t_minishell *shell, char *and_word,
			int *heredoc_index, int *pipe_fd)
{
	char	*content;

	cmdclear(&shell->command);
	free_lst_env(shell->env);
	content = NULL;
	ft_sig_handle();
	content = here_read(content, and_word);
	free(and_word);
	if (content == NULL)
	{
		close(pipe_fd[1]);
		exit(0);
	}
	save_content(content, heredoc_index, pipe_fd);
}
