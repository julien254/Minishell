/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:53:59 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/26 10:00:31 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static int	add_cmd(t_minishell *shell, char **cmd_tab, t_set_fd set_fd)
{
	if (!shell->command)
		shell->command = cmdnew(cmd_tab[0], &cmd_tab[0], &set_fd);
	else
		cmdadd_back(&shell->command, cmdnew(cmd_tab[0], &cmd_tab[0],
				&set_fd));
	if (!shell->command)
	{
		printf("minishell: memerror\n");
		return (1);
	}
	return (0);
}

int set_hendle_size(char *block, int i)
{
	int	y;

	y = 0;
	i++;
	while (block[i] && block[i] != ' ' && block[i] != '$' && block[i] != '\'' && block[i] != '/' && block[i] != '"')//fonction de verification
	{
		i++;
		y++;
	}
	return (y);
}

char	*hendle_set(t_minishell *shell, char *block)
{
	int	i;
	int	y;

	i = 0;
	if (!block)
		return (NULL);
	while (block[i])
	{
		y = 0;
		while (block[i] == '\'')
			i = skip_quotes(block, i);
		if (block[i] == '$')
		{
			if (block[i + 1] == '?')
				block = hendles_error(ft_strdup(block), i, shell->exit_code);
			else
			{
				y = 1 + set_hendle_size(block, i);
				block = replace_handle(ft_strdup(block), i, y, shell->env);
			}
		}
		if (!block)
			return (NULL);
		i++;
	}
	return (block);
}

static int	split_block(t_minishell *shell, int old_i, int i)
{
	char		*block;
	char		**cmd_tab;
	t_set_fd	set_fd;

	set_fd.fd_out = 1;
	set_fd.fd_in = 0;
	set_fd.error = 0;
	block = ft_substr(shell->read, old_i, i - old_i);
	if (!block)
		set_fd.error = 1;
	block = hendle_set(shell, block);
	block = set_redirect(shell, block, &set_fd);
	if (set_fd.error == 1)
	{
		printf("minishell: memerror\n");
		return (1);
	}
	if (!block)
		return (1);
	cmd_tab = quote_split(block);
	free(block);
	if (!cmd_tab)
	{
		printf("minishell: memerror\n");
		return (1);
	}
	if (add_cmd(shell, cmd_tab, set_fd))
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
	while (shell->read[i])
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
	//if (shell->command)  //debuger
		//print_cmd(shell->command);
	return (0);
}
