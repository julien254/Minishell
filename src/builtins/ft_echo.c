/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 07:29:32 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/08 08:04:30 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
static int check_option(char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return (0);
	if (arg[i] == '-')
		i++;
	else
		return (0);
	while (arg[i])
	{
		if (arg[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}

void ft_echo(t_minishell *shell, char **args)
{
	int	i;
	int	option;

	option = 0;
	i = 1;
	while (check_option(args[i]))
		i++;
	if (i != 1)
		option = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!option)
		ft_putstr_fd("\n", 1);
	shell->exit_code = 0;
}
