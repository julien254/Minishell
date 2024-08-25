/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:44:39 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/21 17:50:21 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef struct s_command_lst
{
	char					*cmd;
	char					**args;
	int						fd_in;
	int						fd_out;
	int						heredoc_index;
	int						fd_pipe[2];
	struct s_command_lst	*next;
}				t_command_lst;

typedef struct s_minishell
{
	t_env			*env;
	t_env			*env_export;
	t_command_lst	*command;
	int				here_doc_nbr;
	char			*read;
	int				exit_code;
}				t_minishell;

#endif
