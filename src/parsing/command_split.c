/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:53:59 by gcannaud          #+#    #+#             */
/*   Updated: 2024/10/14 12:16:32 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static int	add_cmd(t_minishell *shell, char **cmd_tab, t_set_fd set_fd)
{
	if (!shell->command)
		shell->command = cmdnew(cmd_tab[0], cmd_tab, &set_fd);
	else
		cmdadd_back(&shell->command, cmdnew(cmd_tab[0], &cmd_tab[0],
				&set_fd));
	if (!shell->command)
	{
		ft_putstr_fd("minishell: memerror\n", 2);
		return (1);
	}
	return (0);
}

static int	set_cmd_struct(char *block, t_minishell *shell, t_set_fd set_fd)
{
	char		**cmd_tab;

	cmd_tab = quote_split(block);
	free(block);
	if (!cmd_tab)
	{
		ft_putstr_fd("minishell: memerror\n", 2);
		return (1);
	}
	if (add_cmd(shell, cmd_tab, set_fd))
		return (1);
	return (0);
}

static int	split_block(t_minishell *shell, int old_i, int i)
{
	char		*block;
	t_set_fd	set_fd;

	set_fd.fd_out = 1;
	set_fd.fd_in = 0;
	set_fd.error = 0;
	block = ft_substr(shell->read, old_i, i - old_i);
	if (!block)
		set_fd.error = 1;
	block = set_redirect(shell, block, &set_fd);
	block = handle_set(shell, block);
	if (set_fd.error == 1)
	{
		ft_putstr_fd("minishell: memerror\n", 2);
		return (1);
	}
	if (!block)
		return (1);
	if (set_cmd_struct(block, shell, set_fd))
		return (1);
	return (0);
}

int	command_split(t_minishell *shell)
{
	int	i;
	int	old_i;

	i = 0;
	old_i = 0;
	shell->command = NULL;
	while (shell->read[i] && shell->read[i] != 0)
	{
		if (shell->read[i] == '"' || shell->read[i] == '\'')
			i = skip_quotes(shell->read, i);
		else if (shell->read[i] == '|' && shell->read[i + 1] != '|')
		{
			if (split_block(shell, old_i, i))
				return (1);
			old_i = i + 1;
		}
		i++;
	}
	if (split_block(shell, old_i, i))
		return (1);
	return (0);
}
