/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:51:56 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/22 12:13:49 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../include/minishell.h"

void	print_cmd(t_command_lst *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		printf("cmd=%s\n", cmd->cmd);
		while (cmd->args[i])
		{
			printf("arg%i=%s\n", i, cmd->args[i]);
			i++;
		}
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

t_command_lst	*cmdnew(char *cmd_name, char **args, int fd_out, int fd_in)
{
	t_command_lst	*cmd;

	cmd = (t_command_lst *)malloc(sizeof(t_command_lst));
	//if (!lst)
		//fonction pour quitter proprement
	cmd->cmd = cmd_name;
	cmd->args = args;
	cmd->fd_out = fd_out;
	cmd->fd_in = fd_in;
	cmd->next = NULL;
	return (cmd);
}
