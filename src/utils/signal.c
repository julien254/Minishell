/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:51:49 by judetre           #+#    #+#             */
/*   Updated: 2024/08/21 12:00:53 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	g_signal = 0;

void	ft_sig_result(int sig)
{
	(void)sig;
	g_signal = 2;
	if (wait(0) == -1)
	{
		ft_printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		ft_printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
	}
}

void	ft_catc(void)
{
	ft_printf("\n");
}

void	ft_sig(void)
{
	signal(SIGINT, ft_sig_result);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_exitsig(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_IGN);
	g_signal = 1;
	close(0);
}

void	ft_sig_handle(void)
{
	signal(SIGINT, ft_exitsig);
	signal(SIGQUIT, SIG_IGN);
}
