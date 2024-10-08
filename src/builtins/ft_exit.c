/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 04:32:36 by judetre           #+#    #+#             */
/*   Updated: 2024/10/10 13:04:52 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int ft_exit(t_minishell *shell, int exec_option)
{
	if (!exec_option)
	{		
		free_lst_env(shell->env);
		if (shell->interactive)
			ft_putstr_fd("exit\n", 2);
	}
	exit(shell->exit_code);
}
