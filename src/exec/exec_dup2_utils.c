/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup2_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:06:17 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/14 14:15:02 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_dup2(int fd_in, int fd_out)
{
	if (dup2(fd_in, 0) == -1)
		perror("dup2");
	if (dup2(fd_out, 1) == -1)
		perror("dup2");
}

void	ft_choose_dup2(t_minishell *shell, char *order)
{
	if (shell->command->fd_in == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(shell->command->fd_in_name);
		shell->exit_code = 1;
		exit(shell->exit_code);
	}
	else if (shell->command->fd_out == -1)
	{
		if (ft_strncmp(order, "last", 4) == 0)
			close(shell->command->fd_pipe[1]);
		ft_putstr_fd("minishell: ", 2);
		perror(shell->command->fd_out_name);
		shell->exit_code = 1;
		exit(shell->exit_code);
	}
	if (ft_strncmp(order, "last", 4) == 0)
		ft_dup2(shell->command->fd_in, shell->command->fd_out);
	else
	{
		if (shell->command->fd_out > 1)
			ft_dup2(shell->command->fd_in, shell->command->fd_out);
		else
			ft_dup2(shell->command->fd_in, shell->command->fd_pipe[1]);
	}
}

void	ft_choose_dup2_with_no_pipe(t_minishell *shell)
{
	if (shell->command->fd_in == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(shell->command->fd_in_name);
		shell->exit_code = 1;
		exit(shell->exit_code);
	}
	else if (shell->command->fd_out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(shell->command->fd_out_name);
		shell->exit_code = 1;
		exit(shell->exit_code);
	}
	ft_dup2(shell->command->fd_in, shell->command->fd_out);
}
