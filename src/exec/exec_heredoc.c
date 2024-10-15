/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:11:02 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/15 12:09:34 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	if_heredoc(t_minishell *shell)
{
	int	fd;

	if (shell->command->heredoc_index)
	{
		fd = open(shell->command->heredoc_name, O_RDONLY);
		if (fd == -1)
		{
			perror("minishell ");
			return ;
		}
		if (shell->command->fd_in > 0)
			close(shell->command->fd_in);
		shell->command->fd_in = fd;
	}
}
