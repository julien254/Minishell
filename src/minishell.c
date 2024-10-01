/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:04:47 by judetre           #+#    #+#             */
/*   Updated: 2024/10/01 11:22:42 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_minishell	shell;
	char str[] = "salut les amies voila le PATH :\n$PATH\net voila le reste de la phrase"; //exemple de str avec un handle que tu vas m'envoyer
	char *str_malloc = ft_strdup(str); // je le malloc pour le free ensuite dans la fonction recup handle.


	(void)argc;
	(void)argv;
	shell.env = recover_env(envp);
	set_tab_path(&shell);
	replace_handle(str_malloc, 32, 5, shell.env);


	/* while (1) */
	/* { */
	/* 	ft_sig(); */
	/* 	shell.read = readline("minishell> "); */
	/* 	if (g_signal == 2) */
	/* 	{ */
	/* 		shell.exit_code = 130; */
	/* 		g_signal = 0; */
	/* 	} */
	/* 	if (!shell.read) */
	/* 		ft_exit(&shell); */
	/* 	if (shell.read[0] != 0) */
	/* 	{ */
	/* 		if (!parse_command(&shell)) */
	/* 		{ */
	/* 			exec_cmd(&shell); */
	/* 			cmdclear(&shell.command); */
	/* 		} */
	/* 	} */
	/* 	//free(shell.read); */
	/* } */

	return (0);
}
