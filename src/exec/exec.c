/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:11:08 by judetre           #+#    #+#             */
/*   Updated: 2024/10/14 14:34:48 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static void	ft_execve(t_minishell *shell)
{
	char	*cmd;
	char	**env;

	cmd = ft_recovery_cmd(shell);
	if (shell->tab_path)
	{
		ft_free_malloc2d((void *)shell->tab_path);
		shell->tab_path = NULL;
	}
	if (!cmd)
	{
		putstr_err_command(shell);
		exit(shell->exit_code);
	}
	env = make_tab_env(shell->env);
	execve(cmd, shell->command->args, env);
	ft_free_malloc2d((void *)env);
	perror("failed execve");
}

static void	ft_pipex(t_minishell *shell, char *order)
{
	shell->command->pid = ft_fork();
	if (shell->command->pid == 0)
	{
		if (strncmp(order, "last", 4) == 0 && shell->command->fd_out != -1)
			close(shell->command->fd_pipe[1]);
		close(shell->command->fd_pipe[0]);
		ft_choose_dup2(shell, order);
		check_err_command(shell);
		if (if_is_builtins(shell))
			exec_builtins(shell, 1);
		ft_execve(shell);
		ft_free_malloc2d((void *)shell->tab_path);
		exit(shell->exit_code);
	}
}

static void	exec_with_no_pipe(t_minishell *shell)
{
	shell->command->pid = ft_fork();
	if (shell->command->pid == 0)
	{
		ft_choose_dup2_with_no_pipe(shell);
		check_err_command(shell);
		if (if_is_builtins(shell))
			exec_builtins(shell, 1);
		ft_execve(shell);
		ft_free_malloc2d((void *)shell->tab_path);
		exit(shell->exit_code);
	}
}

static void	launch_all_command(t_minishell *shell)
{
	while (shell->command)
	{
		ft_pipe(shell);
		if (!shell->command->next)
			ft_pipex(shell, "last");
		else
			ft_pipex(shell, "first");
		if (shell->command->fd_in > 0)
			close(shell->command->fd_in);
		if (shell->command->next && shell->command->next->fd_in == 0)
			shell->command->next->fd_in = shell->command->fd_pipe[0];
		else
			close(shell->command->fd_pipe[0]);
		close(shell->command->fd_pipe[1]);
		shell->command = shell->command->next;
	}
}

void	exec_cmd(t_minishell *shell)
{
	int				status;
	t_command_lst	*command_lst;

	command_lst = shell->command;
	if (!shell->command->next && if_is_builtins_exec_in_parent(shell))
	{
		exec_builtins(shell, 0);
		return ;
	}
	else if (!shell->command->next)
		exec_with_no_pipe(shell);
	else
		launch_all_command(shell);
	while (command_lst)
	{
		waitpid(command_lst->pid, &status, 0);
		set_exit_code(shell, status);
		if (command_lst->fd_out && command_lst->fd_out > 1)
			close(command_lst->fd_out);
		if (command_lst->fd_in && command_lst->fd_in > 0)
			close(command_lst->fd_in);
		command_lst = command_lst->next;
	}
}
