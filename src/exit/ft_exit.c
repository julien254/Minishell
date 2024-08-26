/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 04:32:36 by judetre           #+#    #+#             */
/*   Updated: 2024/08/26 05:21:31 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int ft_exit(t_minishell *shell)
{
	free_lst_env(shell->env);
	ft_putstr_fd("EXIT\n", 2);
	exit(shell->exit_code);
}
