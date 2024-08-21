/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:53:59 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/21 19:23:27 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static void	split_block(t_minishell *shell, int old_i, int i)
{
	char	*block;
	char	**cmd_tab;

	block = ft_substr(shell->read, old_i, i - old_i);
	if (!block)
		return ; //a securiser
	//cmd_tab = hendle
	cmd_tab = quote_split(block, ' '); //REPRIS DE MON MINISHELL /!\ ENTIERMENT A REFAIRE
	if (!shell->command)
		shell->command = cmdnew(cmd_tab[0], &cmd_tab[1]);
	else
		cmdadd_back(&shell->command, cmdnew(cmd_tab[0], &cmd_tab[1]));
}

int skip_quotes(char *str, int i)
{
	char quote;

	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

void	command_split(t_minishell *shell)
{
	int	i;
	int old_i;

	i = 0;
	old_i = 0;
	while (shell->read[i])
	{
		if (shell->read[i] == '"' || shell->read[i] == '\'')
			i = skip_quotes(shell->read, i);
		else if (shell->read[i] == '|' && shell->read[i + 1] == '|')
		{
			split_block(shell, old_i, i);
			old_i = i + 1;
		}
		i++;
	}
	split_block(shell, old_i, i);
	if (shell->command)
		print_cmd(shell->command);
}
