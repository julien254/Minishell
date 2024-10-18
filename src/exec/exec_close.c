/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:12:32 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/18 15:21:38 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	close_all_fd(t_command_lst *lst_command)
{
	if (lst_command->fd_out && lst_command->fd_out > 1)
		close(lst_command->fd_out);
	if (lst_command->fd_in && lst_command->fd_in > 0)
		close(lst_command->fd_in);
}
