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

static void	cmddelone(t_command_lst *cmd)
{
	int	i;

	i = 1;
	if (cmd)
	{
		free(cmd->cmd);
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
