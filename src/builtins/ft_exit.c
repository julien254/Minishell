/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 04:32:36 by judetre           #+#    #+#             */
/*   Updated: 2024/10/12 17:25:57 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
int	is_num_arg(char *)
{
	
}

int ft_exit(t_minishell *shell, int exec_option)
{

	int			size;
	long int	exit_code;

	if (shell->command)
	{
		size = ft_tab2dlen(shell->command->args);
		if (size > 2)
		{	
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			shell->exit_code = 1;
			return (1);
		}
		else if (size == 2)
		{
			exit_code = ft_atoi(shell->command->args[1]);
		}
	}
	if (!exec_option)
	{		
		free_lst_env(shell->env);
		if (shell->interactive)
			ft_putstr_fd("exit\n", 2);
	}
	exit(shell->exit_code);
}
