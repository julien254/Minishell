/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:25:49 by judetre           #+#    #+#             */
/*   Updated: 2024/08/22 07:34:27 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell.env = recover_env(envp);
	print_env(shell.env);
	shell.env_export = lst_env_cpy(shell.env);
	sort_list(shell.env_export);
	printf("\n\n\n\n\n\n\n");
	print_env(shell.env_export);
	printf("\n\n\n\n\n\n\n");
	print_env(shell.env);
	
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
	/* 		exit(EXIT_SUCCESS); */
	/* 	if (shell.read[0] != '\0') */
	/* 	parse_command(&shell); */
	/* 	cmdclear(&shell.command); */
	/* 	//free(shell.read); */
	/* } */

	return (0);
}
