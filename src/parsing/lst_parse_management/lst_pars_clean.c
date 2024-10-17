/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pars_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:51:56 by gcannaud          #+#    #+#             */
/*   Updated: 2024/10/17 17:57:08 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../include/minishell.h"

static void	cmddelone(t_command_lst *cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		if (cmd->args)
		{
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		if (cmd->fd_in_name)
			free(cmd->fd_in_name);
		if (cmd->fd_out_name)
			free(cmd->fd_out_name);
		if (cmd->heredoc_name)
			free(cmd->heredoc_name);
		if (cmd->fd_pipe_del)
			close(cmd->fd_pipe_del);
		free(cmd);
	}
}

void	cmdclear(t_command_lst **cmd)
{
	t_command_lst	*temp;

	if (cmd && *cmd)
	{
		while (*cmd)
		{
			temp = (*cmd)->next;
			cmddelone(*cmd);
			*cmd = temp;
		}
	}
}
