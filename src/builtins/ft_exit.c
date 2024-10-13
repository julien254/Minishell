/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 04:32:36 by judetre           #+#    #+#             */
/*   Updated: 2024/10/13 14:42:48 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
static int	is_white_space(char c)
{
	if ((c < '\t' || c > '\r') && c != ' ')
		return (0);
	return (1);
}

static long int	ft_atol_exit(const char *str)
{
	size_t		i;
	long int	isneg;
	long int	nbr;

	i = 0;
	isneg = 1;
	while (is_white_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			isneg = -1;
		i++;
	}
	nbr = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * isneg);
}

static int	is_num_arg(char *str)
{
	int	size;
	int	i;
	int	is_neg;

	i = 0;
	size = 0;
	is_neg = 0;
	while (is_white_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			is_neg = 1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		i++;
		size++;
	}
	while (is_white_space(str[i]))
		i++;
	if (!is_neg && (size > 19 || (size == 19 && ft_atol_exit(str) < 0)))
		return (0);
	if (is_neg && (size > 19 || (size == 19 && ft_atol_exit(str) > 0)))
		return (0);
	if (!str[i])
		return (1);
	return (0);	
}

int ft_exit(t_minishell *shell, int exec_option)
{

	int		size;
	char	exit_code;
	int		first_arg_is_good;

	if (shell->command)
	{
		size = ft_tab2dlen(shell->command->args);
		if (size >= 2)
		{	
			if (!is_num_arg(shell->command->args[1]))
			{
				first_arg_is_good = 0;
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(shell->command->args[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				shell->exit_code = 2;

			}
			else
			{
				first_arg_is_good = 1;
				exit_code = (char)ft_atol_exit(shell->command->args[1]);
				shell->exit_code = exit_code;
			}
		}
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
		if (shell->interactive)
			ft_putstr_fd("exit\n", 2);
	}
	exit(shell->exit_code);
}
