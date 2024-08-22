/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:57:27 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/22 05:50:40 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_command_lst
{
	char					*file; //renam cmd
	char					**args;
	int						fd_in;
	int						fd_out;
	int						fd_pipe[2];
	struct s_command_lst	*next;
}				t_command_lst;

void			print_cmd(t_command_lst *cmd);
t_command_lst	*cmdlast(t_command_lst *cmd);
void			cmdadd_back(t_command_lst **cmd, t_command_lst *cmd_new);
t_command_lst	*cmdnew(char *file, char **args);
void			cmdclear(t_command_lst **cmd);

#endif
