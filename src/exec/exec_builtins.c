/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:43:59 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/18 15:24:15 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static void	close_fd(t_minishell *shell)
{
	t_command_lst	*command_lst;

	command_lst = shell->command;
	while (command_lst)
	{
		if (command_lst->fd_in > 0)
			close(command_lst->fd_in);
		if (command_lst->fd_out > 1)
			close(command_lst->fd_out);
		command_lst = command_lst->next;
	}
	if (shell->command->fd_pipe[0])
		close(shell->command->fd_pipe[0]);
	if (shell->command->fd_pipe[1])
		close(shell->command->fd_pipe[1]);
}

int	if_is_builtins_exec_in_parent(t_minishell *shell)
{
	if (shell->command->cmd == NULL)
		return (0);
	if (ft_strcmp(shell->command->cmd, "export") == 0)
		return (1);
	if (ft_strcmp(shell->command->cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(shell->command->cmd, "exit") == 0)
	{
		if (shell->command->fd_in != -1 && shell->command->fd_out != -1)
			return (1);
	}
	if (ft_strcmp(shell->command->cmd, "cd") == 0)
		return (1);
	return (0);
}

int	if_is_builtins(t_minishell *shell)
{
	if (shell->command->cmd == NULL)
		return (0);
	if (ft_strcmp(shell->command->cmd, "export") == 0)
		return (1);
	if (ft_strcmp(shell->command->cmd, "env") == 0)
		return (1);
	if (ft_strcmp(shell->command->cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(shell->command->cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(shell->command->cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(shell->command->cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(shell->command->cmd, "cd") == 0)
		return (1);
	return (0);
}

int	exec_builtins(t_minishell *shell, int exit_option)
{
	if (ft_strcmp(shell->command->cmd, "export") == 0)
		ft_export(shell, shell->command->args);
	if (ft_strcmp(shell->command->cmd, "env") == 0)
		ft_env(shell->env);
	if (ft_strcmp(shell->command->cmd, "unset") == 0)
		ft_unset(shell, shell->command->args);
	if (ft_strcmp(shell->command->cmd, "exit") == 0)
		ft_exit(shell, exit_option);
	if (ft_strcmp(shell->command->cmd, "pwd") == 0)
		ft_pwd();
	if (ft_strcmp(shell->command->cmd, "echo") == 0)
		ft_echo(shell, shell->command->args);
	if (ft_strcmp(shell->command->cmd, "cd") == 0)
		shell->exit_code = ft_cd(shell, shell->command->args);
	if (exit_option)
	{
		free_lst_env(shell->env);
		close_fd(shell);
		cmdclear(&shell->start_lst_command);
		exit(shell->exit_code);
	}
	close_fd(shell);
	return (shell->exit_code);
}
