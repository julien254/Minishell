/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:11:08 by judetre           #+#    #+#             */
/*   Updated: 2024/10/12 16:19:39 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"


int	if_is_builtins_exec_in_parent(t_minishell *shell)
{
	if (shell->command->cmd == NULL)
		return (0);
	if (ft_strcmp(shell->command->cmd, "export") == 0)
	{
		if (ft_tab2dlen(shell->command->args) == 1)
			return (1);
	}
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

static int	exec_builtins(t_minishell *shell, int exit_option)
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
		shell->exit_code = ft_cd(shell->command->args);
	if (exit_option)
		exit(shell->exit_code);
	return (shell->exit_code);
}

void	set_exit_code(t_minishell *shell,int status)
{
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
}

static int	if_backslash(char *str)
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

int is_directory(t_minishell *shell) {
	struct stat path_stat;

	if (stat(shell->command->cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(shell->command->cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		shell->command->wrong_cmd = 2;
		shell->exit_code = 126;
		return 1;
	}
	return 0;
}

static char	*ft_recovery_cmd(t_minishell *shell)
{
	size_t	i;
	char	*cmd;
	char	*tmp;

	i = 0;
	shell->tab_path = set_tab_path(shell);
	if (if_backslash(shell->command->cmd))
	{
		if (access(shell->command->cmd, F_OK | X_OK) == 0 && !is_directory(shell))
			return (shell->command->cmd);
	}
	else if (shell->command->cmd)
	{
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
			if (access(cmd, F_OK | X_OK) == 0 && !is_directory(shell))
				return (cmd);
			free(cmd);
		}
		if (!shell->command->wrong_cmd)
			shell->command->wrong_cmd = 1;
	}
	return (NULL);
}

void	check_err_command(t_minishell *shell)
{
	char *cmd;

	if (shell->command->cmd)
	{
		if (ft_strcmp(shell->command->args[0], "") == 0)
		{
			ft_putstr_fd(" : command not found\n", 2);
			shell->exit_code = 127;
			exit(shell->exit_code);
		}
		if (ft_strcmp(shell->command->args[0], ".") == 0)
		{
			if (shell->command->args[1])
			{
				free(shell->command->cmd);
				shell->command->cmd = ft_strdup(shell->command->args[1]);
				cmd = ft_recovery_cmd(shell);
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
				exit(shell->exit_code);
			}
			else
			{
				ft_putstr_fd("minishell: .: file name required as argument\n", 2);
				shell->exit_code = 2;
				exit(shell->exit_code);
			}
		}
	}
}

static void	putstr_err_command(t_minishell *shell)
{
	if (shell->command->cmd)
	{
		if (!shell->command->wrong_cmd)
		{
			if (errno == EACCES)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(shell->command->cmd, 2);
				ft_putstr_fd(": Permission denied\n", 2);
				shell->exit_code = 126;
				return ;
			}
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(shell->command->cmd, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else if (shell->command->wrong_cmd == 1)
		{
			ft_putstr_fd(shell->command->cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		if (shell->command->wrong_cmd != 2)
			shell->exit_code = 127;
	}
}

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

void	ft_pipex(t_minishell *shell, char *order)
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

void	exec_with_no_pipe(t_minishell *shell)
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

void	exec_cmd(t_minishell *shell)
{
	int				status;
	t_command_lst	*command_lst;

	command_lst = shell->command;
	if (!shell->command->next && if_is_builtins_exec_in_parent(shell))
	{
		//print_cmd(shell->command);
		exec_builtins(shell, 0);
		return;
	}
	else if (!shell->command->next)
	{
		//print_cmd(shell->command);
		exec_with_no_pipe(shell);
	}
	else
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
