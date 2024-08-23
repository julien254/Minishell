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

static int	split_block(t_minishell *shell, int old_i, int i)
{
	char	*block;
	char	**cmd_tab;
	int		fd_out;
	int		fd_in;
	int		error;// le contenu de block peux estre a null dans le cas d'un malloc error MAI ausi pour une erreure de redirection, au quelle cas, les autre pipe s'executron toujour

	fd_out = 1;
	fd_in = 0;
	block = ft_substr(shell->read, old_i, i - old_i);
	if (!block)
		return (1); //a securiser
	//block = hendle
	block = set_redirect(block, &fd_out, &fd_in, &error);
	if (!block && error)
		return (1); //a securiser
	cmd_tab = quote_split(block);
	if (!cmd_tab)
		return (1); //a securiser(malloc error)
	if (!shell->command)
		shell->command = cmdnew(cmd_tab[0], &cmd_tab[1], fd_out, fd_in);
	else
		cmdadd_back(&shell->command, cmdnew(cmd_tab[0], &cmd_tab[1], fd_out, fd_in));
	//proteger cmdnew
	return (0);
}

void	command_split(t_minishell *shell)
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
				return ;
			old_i = i + 1;
		}
		i++;
	}
	if (split_block(shell, old_i, i))
		return ;
	if (shell->command)
		print_cmd(shell->command);
}
