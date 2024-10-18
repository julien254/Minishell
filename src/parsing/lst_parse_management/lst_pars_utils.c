/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:51:56 by gcannaud          #+#    #+#             */
/*   Updated: 2024/10/18 15:49:27 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../include/minishell.h"

t_command_lst	*cmdlast(t_command_lst *cmd)
{
	while (cmd)
	{
		if (cmd->next == NULL)
			return (cmd);
		cmd = cmd->next;
	}
	return (0);
}

void	cmdadd_back(t_command_lst **cmd, t_command_lst *cmd_new)
{
	t_command_lst	*last;

	if (!(*cmd))
		*cmd = cmd_new;
	else
	{
		last = cmdlast(*cmd);
		last->next = cmd_new;
	}
}

t_command_lst	*cmdnew(char *cmd_name, char **args, t_set_fd *set_fd)
{
	t_command_lst	*cmd;

	cmd = (t_command_lst *)malloc(sizeof(t_command_lst));
	if (!cmd)
		return (NULL);
	cmd->cmd = cmd_name;
	cmd->args = args;
	cmd->fd_out = set_fd->fd_out;
	cmd->fd_in = set_fd->fd_in;
	cmd->fd_in_name = set_fd->fd_in_name;
	cmd->fd_out_name = set_fd->fd_out_name;
	cmd->heredoc_index = set_fd->heredoc_index;
	cmd->heredoc_name = set_fd->heredoc_name;
	cmd->wrong_cmd = 0;
	cmd->fd_pipe[0] = 0;
	cmd->fd_pipe[1] = 0;
	cmd->fd_pipe_del = 0;
	cmd->next = NULL;
	return (cmd);
}
