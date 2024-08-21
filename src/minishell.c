/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:25:49 by judetre           #+#    #+#             */
/*   Updated: 2024/08/21 12:11:22 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	t_minishell shell;

	shell.env = recover_env(envp);
	while (1)
	{
		ft_sig();
		shell.read = readline("minishell> ");
		if (g_signal == 2)
		{
			shell.exit_code = 130;
			g_signal = 0;
		}
		if (!shell.read)
			exit(EXIT_SUCCESS);
	}
	return (0);
}
