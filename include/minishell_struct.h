/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:44:39 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/26 07:26:02 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef struct s_command_lst
{
	char					*cmd;
	char					**args;
	int						pid;
	int						fd_in;
	int						fd_out;
	int						heredoc_index;
	int						fd_pipe[2];
	struct s_command_lst	*next;
}				t_command_lst;

typedef struct s_minishell
{
	t_env			*env;
	t_command_lst	*command;
	char			**tab_path;
	int				here_doc_nbr;
	char			*read;
	int				exit_code;
}				t_minishell;

#endif
