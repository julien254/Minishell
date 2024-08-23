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
	char					*cmd;
	char					**args;
	int						fd_in;
	int						fd_out;
	int						fd_pipe[2];
	struct s_command_lst	*next;
}				t_command_lst;

/**************************** LST_UTILS_CMD *********************************/

void			print_cmd(t_command_lst *cmd);
t_command_lst	*cmdlast(t_command_lst *cmd);
void			cmdadd_back(t_command_lst **cmd, t_command_lst *cmd_new);
t_command_lst	*cmdnew(char *cmd_name, char **args, int fd_out, int fd_in);

/**************************** LST_CMD_CLEAR *********************************/

void			cmdclear(t_command_lst **cmd);

/**************************** SET_REDIRECT *********************************/

char			*set_redirect(char *block, int *fd_out, int *fd_in, int *error);
char			*set_file_name(char *block, int *i);

#endif
