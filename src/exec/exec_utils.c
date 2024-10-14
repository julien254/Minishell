/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:19:46 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/14 14:23:27 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("Fork");
	return (pid);
}

void	ft_pipe(t_minishell *shell)
{
	if (pipe(shell->command->fd_pipe) == -1)
		perror("Pipe");
}

void	set_exit_code(t_minishell *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
}

int	if_backslash(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

int	is_directory(t_minishell *shell)
{
	struct stat	path_stat;

	if (stat(shell->command->cmd, &path_stat) == 0 && \
			S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(shell->command->cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		shell->command->wrong_cmd = 2;
		shell->exit_code = 126;
		return (1);
	}
	return (0);
}
