/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:11:08 by judetre           #+#    #+#             */
/*   Updated: 2024/10/04 11:23:36 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static char	*ft_recovery_cmd(t_minishell *shell)
{
	size_t	i;
	char	*cmd;
	char	*tmp;

	i = 0;
	shell->tab_path = set_tab_path(shell);
	if (access(shell->command->cmd, F_OK | X_OK) == 0)
			return (shell->command->cmd);
	while (shell->tab_path && shell->tab_path[i])
	{
		tmp = ft_strjoin(shell->tab_path[i++], "/");
		if (!tmp)
			return (NULL);
		cmd = ft_strjoin(tmp, shell->command->cmd);
		if (!cmd)
		{
			free(tmp);
			return (NULL);
		}
		free(tmp);
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		free(cmd);
	}
	return (NULL);
}

/* char	*cut_cmd(t_command_lst *command) */
/* { */
/* 	char	**tab_cmd; */
/* 	int		size; */
/* 	char	*cmd; */
/* 	tab_cmd = ft_split(command->cmd, '/'); */
/* 	if (!tab_cmd) */
/* 		return (NULL); */
/* 	size = ft_tab2dlen(tab_cmd); */
/* 	cmd = ft_strdup(tab_cmd[size - 1]); */
/* 	free(command->cmd); */
/* 	ft_free_malloc2d((void *)tab_cmd); */
/* 	if (!cmd) */
/* 		return (NULL); */
/* 	return (cmd); */
/* } */

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
		ft_putstr_fd("Minishell: ", 2);
		//shell->command->cmd = cut_cmd(shell->command);
		ft_putstr_fd(shell->command->cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	env = make_tab_env(shell->env);
	execve(cmd, shell->command->args, env);
	ft_free_malloc2d((void*)env);
	perror("failed execve");
}

static pid_t	ft_fork(void)
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

void	ft_dup2(int fd_in, int fd_out)
{
	if (dup2(fd_in, 0) == -1)
		perror("dup2");
	if (dup2(fd_out, 1) == -1)
		perror("dup2");
}

void	ft_choose_dup2(t_minishell *shell, char *order)
{
	if (ft_strncmp(order, "last", 4) == 0)
	{
		if (shell->command->fd_out == -1)
        	shell->command->fd_out = shell->command->fd_pipe[1];  
		ft_dup2(shell->command->fd_in, shell->command->fd_out);
	}
	else
		ft_dup2(shell->command->fd_in, shell->command->fd_pipe[1]);
}

void	ft_pipex(t_minishell *shell, char *order)
{

	shell->command->pid = ft_fork();
	if (shell->command->pid == 0)
	{
		if (strncmp(order, "last", 4) == 0 && shell->command->fd_out != -1)
			close(shell->command->fd_pipe[1]);
		close(shell->command->fd_pipe[0]);
        ft_choose_dup2(shell, order);
		ft_execve(shell);
        ft_free_malloc2d((void *)shell->tab_path);
        exit(0);
	}
}

void	exec_cmd(t_minishell *shell)
{
	t_command_lst	*command_lst;
	
	command_lst = shell->command;
	while (shell->command)
	{
		ft_pipe(shell);		
		if (!shell->command->next)
			ft_pipex(shell, "last");
		else
			ft_pipex(shell, "first");
		if (shell->command->fd_in > 0)
			close(shell->command->fd_in);
		if (shell->command->next)
			shell->command->next->fd_in = shell->command->fd_pipe[0];
		else
        	close(shell->command->fd_pipe[0]);
        close(shell->command->fd_pipe[1]);
		shell->command = shell->command->next;
	}
	while (command_lst)
	{
		waitpid(command_lst->pid, NULL, 0);
		if (command_lst->fd_out && command_lst->fd_out > 1)
			close(command_lst->fd_out);
		command_lst = command_lst->next;
	}
}
