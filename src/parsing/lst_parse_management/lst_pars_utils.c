/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:51:56 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/26 06:03:22 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../include/minishell.h"

void	print_cmd(t_command_lst *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		printf("|--------------------\n");
		printf("|cmd=%s\n", cmd->cmd);
		while (cmd->args[i])
		{
			printf("|arg%i=%s\n", i, cmd->args[i]);
			i++;
		}
		printf("|fd_in :%d\n", cmd->fd_in);
		printf("|fd_out :%d\n", cmd->fd_out);
		printf("|heredoc_index :%d\n", cmd->heredoc_index);
		printf("|pipe[0] :%d , pipe[1] :%d\n", cmd->fd_pipe[0], cmd->fd_pipe[1]);
		printf("|--------------------\n");
		i = 0;
		cmd = cmd->next;
	}
}

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
	cmd->heredoc_index = set_fd->heredoc_index;
	cmd->next = NULL;
	return (cmd);
}
