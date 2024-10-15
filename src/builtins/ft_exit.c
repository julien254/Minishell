/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 04:32:36 by judetre           #+#    #+#             */
/*   Updated: 2024/10/15 17:07:33 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static void	if_is_neg(char c, int *i, int *is_neg)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			*is_neg = 1;
		(*i)++;
	}
}

static int	is_num_arg(char *str)
{
	int	size;
	int	i;
	int	is_neg;

	i = 0;
	size = 0;
	is_neg = 0;
	while (ft_is_white_space(str[i]))
		i++;
	if_is_neg(str[i], &i, &is_neg);
	while (ft_isdigit(str[i]))
	{
		i++;
		size++;
	}
	while (ft_is_white_space(str[i]))
		i++;
	if (!is_neg && (size > 19 || (size == 19 && ft_atol_exit(str) < 0)))
		return (0);
	if (is_neg && (size > 19 || (size == 19 && ft_atol_exit(str) > 0)))
		return (0);
	if (!str[i])
		return (1);
	return (0);
}

static void	check_first_arg(t_minishell *shell, int *arg_is_good)
{
	char	exit_code;

	if (!is_num_arg(shell->command->args[1]))
	{
		*arg_is_good = 0;
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(shell->command->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		shell->exit_code = 2;
	}
	else
	{
		*arg_is_good = 1;
		exit_code = (char)ft_atol_exit(shell->command->args[1]);
		shell->exit_code = exit_code;
	}
}

int	ft_exit(t_minishell *shell, int exec_option)
{
	int		size;
	int		first_arg_is_good;

	if (shell->command)
	{
		size = ft_tab2dlen(shell->command->args);
		if (size >= 2)
			check_first_arg(shell, &first_arg_is_good);
		if (size > 2 && first_arg_is_good)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			shell->exit_code = 1;
			return (1);
		}
	}
	if (!exec_option)
	{
		free_lst_env(shell->env);
		if (shell->command)
			cmdclear(&shell->command);
		if (shell->interactive)
			ft_putstr_fd("exit\n", 2);
	}
	exit(shell->exit_code);
}
