/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:11:08 by judetre           #+#    #+#             */
/*   Updated: 2024/10/01 12:08:49 by jdetre           ###   ########.fr       */
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

static void	ft_execve(t_minishell *shell)
{
	char			*cmd;

	cmd = ft_recovery_cmd(shell);
	if (shell->tab_path)
	{
		ft_free_malloc2d((void *)shell->tab_path);
		shell->tab_path = NULL;
	}
	if (!cmd)
	{
		ft_putstr_fd("Minishell: Command not found: ", 2);
		ft_putstr_fd(shell->command->cmd, 2);
		ft_putstr_fd("\n", 2);
	}
	execve(cmd, shell->command->args, NULL);
}

static pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("Fork");
	return (pid);
}

void	exec_cmd(t_minishell *shell)
{
	shell->command->pid = ft_fork();
	if (shell->command->pid == 0)
	{
		ft_execve(shell);
		exit(EXIT_FAILURE);
	}
	waitpid(shell->command->pid, NULL, 0);
}
