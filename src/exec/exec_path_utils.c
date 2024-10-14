/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:30:35 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/14 14:33:36 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static char	*make_path(t_minishell *shell, size_t *i)
{
	char	*tmp;
	char	*cmd;

	tmp = ft_strjoin(shell->tab_path[(*i)++], "/");
	if (!tmp)
		return (NULL);
	cmd = ft_strjoin(tmp, shell->command->cmd);
	if (!cmd)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (cmd);
}

static void	set_wrong_cmd(t_minishell *shell)
{
	if (!shell->command->wrong_cmd)
		shell->command->wrong_cmd = 1;
}

char	*ft_recovery_cmd(t_minishell *shell)
{
	size_t	i;
	char	*cmd;

	i = 0;
	shell->tab_path = set_tab_path(shell);
	if (if_backslash(shell->command->cmd))
	{
		if (access(shell->command->cmd, F_OK | X_OK) == 0 && \
				!is_directory(shell))
			return (shell->command->cmd);
	}
	else if (shell->command->cmd)
	{
		while (shell->tab_path && shell->tab_path[i])
		{
			cmd = make_path(shell, &i);
			if (!cmd)
				return (NULL);
			if (access(cmd, F_OK | X_OK) == 0 && !is_directory(shell))
				return (cmd);
			free(cmd);
		}
		set_wrong_cmd(shell);
	}
	return (NULL);
}
