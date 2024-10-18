/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:54:17 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/18 15:48:15 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static void	close_fd(t_minishell *shell)
{
	t_command_lst	*command_lst;

	command_lst = shell->command;
	while (command_lst)
	{
		if (shell->command->fd_in > 0)
			close(shell->command->fd_in);
		if (command_lst->fd_out > 1)
			close(command_lst->fd_out);
		command_lst = command_lst->next;
	}
	if (shell->command->fd_pipe[0])
		close(shell->command->fd_pipe[0]);
	if (shell->command->fd_pipe[1])
		close(shell->command->fd_pipe[1]);
}

static void	exit_clean(t_minishell *shell)
{
	free_lst_env(shell->env);
	close_fd(shell);
	cmdclear(&shell->start_lst_command);
	exit(shell->exit_code);
}

static void	print_good_err(t_minishell *shell)
{
	char	*cmd;

	free(shell->command->cmd);
	shell->command->cmd = ft_strdup(shell->command->args[1]);
	cmd = ft_recovery_cmd(shell, 0);
	if (!cmd)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(shell->command->cmd, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		shell->exit_code = 1;
		exit(shell->exit_code);
	}
	ft_putstr_fd("minishell: .: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": cannot execute binary file\n", 2);
	shell->exit_code = 126;
	free(cmd);
	exit_clean(shell);
}

void	check_err_command(t_minishell *shell)
{
	if (shell->command->cmd)
	{
		if (ft_strcmp(shell->command->args[0], "") == 0 || \
				ft_strcmp(shell->command->args[0], "..") == 0)
		{
			ft_putstr_fd(shell->command->args[0], 2);
			ft_putstr_fd(" : command not found\n", 2);
			shell->exit_code = 127;
			exit_clean(shell);
		}
		if (ft_strcmp(shell->command->args[0], ".") == 0)
		{
			if (shell->command->args[1])
				print_good_err(shell);
			else
			{
				ft_putstr_fd("minishell: .: filename argument required\n", 2);
				ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
				shell->exit_code = 2;
				exit_clean(shell);
			}
		}
	}
}

void	putstr_err_command(t_minishell *shell)
{
	if (shell->command->cmd)
	{
		if (!shell->command->wrong_cmd)
		{
			if (errno == EACCES)
			{
				print_invalid_perm(shell);
				close_fd(shell);
				shell->exit_code = 126;
				return ;
			}
			print_no_file(shell);
		}
		else if (shell->command->wrong_cmd == 1)
		{
			ft_putstr_fd(shell->command->cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		if (shell->command->wrong_cmd != 2)
			shell->exit_code = 127;
	}
	close_fd(shell);
}
