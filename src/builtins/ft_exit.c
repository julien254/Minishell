/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 04:32:36 by judetre           #+#    #+#             */
/*   Updated: 2024/10/18 15:08:11 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static void	free_command(t_minishell *shell)
{
	t_command_lst	*command_lst;

	free_lst_env(shell->env);
	if (shell->command)
	{
		command_lst = shell->command;
		while (command_lst)
		{
			if (command_lst->fd_in > 0)
				close(command_lst->fd_in);
			if (command_lst->fd_out > 1)
				close(command_lst->fd_out);
			command_lst = command_lst->next;
		}
		if (shell->command->fd_pipe[1])
			close(shell->command->fd_pipe[1]);
		cmdclear(&shell->start_lst_command);
	}
}

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

static void	check_first_arg(t_minishell *shell, int *arg_is_good, \
		int exec_option)
{
	char	exit_code;

	if (!is_num_arg(shell->command->args[1]))
	{
		*arg_is_good = 0;
		if (!exec_option && shell->interactive)
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
			check_first_arg(shell, &first_arg_is_good, exec_option);
		if (size > 2 && first_arg_is_good)
		{
			if (!exec_option && shell->interactive)
				ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			shell->exit_code = 1;
			return (1);
		}
	}
	if (!exec_option)
	{
		if (shell->interactive)
			ft_putstr_fd("exit\n", 2);
	}
	free_command(shell);
	exit(shell->exit_code);
}
