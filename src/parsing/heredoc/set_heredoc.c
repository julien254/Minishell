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

static int	handle_parent_process(t_set_fd *set_fd, int pipe_fd[2], pid_t pid,
		int *exit_code)
{
	int		status;
	char	*tmp;

	status = 0;
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*exit_code = WEXITSTATUS(status);
	read(pipe_fd[0], &set_fd->heredoc_index, sizeof(int));
	tmp = ft_itoa(set_fd->heredoc_index);
	set_fd->heredoc_name = ft_strjoin("/tmp/heredoc", tmp);
	if (tmp)
		free(tmp);
	if (set_fd->heredoc_name == NULL)
		return (1);
	close(pipe_fd[0]);
	return (0);
}

static int	handle_fork_and_write(t_minishell *shell, t_set_fd *set_fd,
	char *file_name, char *block)
{
	pid_t	pid;
	int		exit_code;
	int		pipe_fd[2];

	exit_code = 0;
	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	set_fd->heredoc_index = shell->here_doc_nbr;
	if (pid == 0)
	{
		free(block);
		close(pipe_fd[0]);
		write_in_term_sav(shell, file_name, &set_fd->heredoc_index, pipe_fd);
	}
	if (handle_parent_process(set_fd, pipe_fd, pid, &exit_code) == 1)
		return (1);
	shell->here_doc_nbr = set_fd->heredoc_index + 1;
	close(pipe_fd[0]);
	return (exit_code);
}

static char	*handle_exit_code(int exit_code, char *block, t_set_fd *set_fd)
{
	if (exit_code == -1)
		return (block);
	if (exit_code == 0)
	{
		if (block)
			free(block);
		unlink(set_fd->heredoc_name);
		free(set_fd->heredoc_name);
		return (NULL);
	}
	if (exit_code == 1)
		set_fd->error = 1;
	return (block);
}

char	*set_heredoc(t_minishell *shell, t_set_fd *set_fd, char *block, int *i)
{
	char	*file_name;
	int		exit_code;
	int		j;

	j = *i;
	file_name = set_file_name(block, i, &shell->exit_code);
	set_fd->heredoc_name = NULL;
	file_name = handle_file_name_error(file_name, block, set_fd);
	if (!file_name)
		return (NULL);
	exit_code = handle_fork_and_write(shell, set_fd, file_name, block);
	free(file_name);
	block = handle_exit_code(exit_code, block, set_fd);
	if (!block)
		return (NULL);
	block = rm_redirect(block, j, *i, &set_fd->error);
	*i = j - 1;
	if (ft_strlen(block) == 0)
		*i = 0;
	return (block);
}
