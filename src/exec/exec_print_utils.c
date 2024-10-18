/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_print_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:30:07 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/18 15:36:34 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	print_invalid_perm(t_minishell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(shell->command->cmd, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

void	print_no_file(t_minishell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(shell->command->cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
