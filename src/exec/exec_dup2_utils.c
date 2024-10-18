/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup2_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:06:17 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/18 12:19:35 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static void	exit_clear(t_minishell *shell)
{
	t_command_lst	*command_lst;

	command_lst = shell->command;
	free_lst_env(shell->env);
	while (command_lst)
	{
		if (command_lst->fd_in > 0)
			close(command_lst->fd_in);
		if (command_lst->fd_out > 1)
			close(command_lst->fd_out);
		command_lst = command_lst->next;
	}
	if (shell->command->fd_pipe[1])
		close(shell->command->fd_pipe[1]);
	cmdclear(&shell->start_lst_command);
	shell->exit_code = 1;
	exit(shell->exit_code);
}

static void	ft_dup2(int fd_in, int fd_out)
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
		exit_clear(shell);
	}
	else if (shell->command->fd_out == -1)
	{
		if (ft_strncmp(order, "last", 4) == 0)
			close(shell->command->fd_pipe[1]);
		ft_putstr_fd("minishell: ", 2);
		perror(shell->command->fd_out_name);
		exit_clear(shell);
	}
	if_heredoc(shell);
	if (ft_strncmp(order, "last", 4) == 0)
		ft_dup2(shell->command->fd_in, shell->command->fd_out);
	else
	{
		if (shell->command->fd_out == 1)
			shell->command->fd_out = shell->command->fd_pipe[1];
		ft_dup2(shell->command->fd_in, shell->command->fd_out);
	}
}

void	ft_choose_dup2_with_no_pipe(t_minishell *shell)
{
	if (shell->command->fd_in == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(shell->command->fd_in_name);
		exit_clear(shell);
	}
	else if (shell->command->fd_out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(shell->command->fd_out_name);
		exit_clear(shell);
	}
	if_heredoc(shell);
	ft_dup2(shell->command->fd_in, shell->command->fd_out);
}
