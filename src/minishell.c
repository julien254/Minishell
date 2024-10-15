/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:04:47 by judetre           #+#    #+#             */
/*   Updated: 2024/10/15 14:33:08 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

static void	setup_readline(t_minishell *msh)
{
	msh->interactive = isatty(STDIN_FILENO);
	rl_outstream = stderr;
	msh->prompt = "minishell> ";
	if (!msh->interactive)
	{
		rl_prep_term_function = 0;
		msh->prompt = NULL;
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_minishell	shell;

	setup_readline(&shell);
	(void)argc;
	(void)argv;
	shell.env = recover_env(envp);
	shell.exit_code = 0;
	while (1)
	{
		ft_sig();
		shell.read = readline(shell.prompt);
		if (g_signal == 2)
		{
			shell.exit_code = 130;
			g_signal = 0;
		}
		shell.command = NULL;
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
		free(shell.read);
	}
	return (0);
}
