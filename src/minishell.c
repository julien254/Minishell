/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:04:47 by judetre           #+#    #+#             */
/*   Updated: 2024/10/09 11:48:47 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_minishell	shell;
	(void)argc;
	(void)argv;
	shell.env = recover_env(envp);
	shell.exit_code = 0;
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
			ft_exit(&shell, 0);
		if (shell.read[0] != 0)
		{
			if (parse_command(&shell) != 0)
			{
				exec_cmd(&shell);
				cmdclear(&shell.command);
			}
		}
		//free(shell.read);
	}
	return (0);
}
