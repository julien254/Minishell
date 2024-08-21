/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pars_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:51:56 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/21 18:45:15 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	print_cmd(t_command_lst *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		printf("cmd=%s\n", cmd->file);
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

t_command_lst	*cmdnew(char *file, char **args)
{
	t_command_lst	*cmd;

	cmd = (t_command_lst *)malloc(sizeof(t_command_lst));
	//if (!lst)
		//fonction pour quitter proprement
	cmd->file = file;
	cmd->args = args;
	cmd->next = NULL;
	return (cmd);
}

static void	cmddelone(t_command_lst *cmd)
{
	int i;

	i = 1;
	if (cmd)
	{
		free(cmd->file);
		//printf("file free\n");
		if (cmd->args[0])
		{
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
		}
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