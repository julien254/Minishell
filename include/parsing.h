/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:57:27 by gcannaud          #+#    #+#             */
/*   Updated: 2024/10/10 13:58:26 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_set_fd
{
	int		fd_out;
	char	*fd_out_name;
	int		fd_in;
	char	*fd_in_name;
	int		heredoc_index;
	int		error;
}				t_set_fd;

/**************************** LST_UTILS_CMD *********************************/

void			print_cmd(t_command_lst *cmd);
t_command_lst	*cmdlast(t_command_lst *cmd);
void			cmdadd_back(t_command_lst **cmd, t_command_lst *cmd_new);
t_command_lst	*cmdnew(char *cmd_name, char **args, t_set_fd *set_fd);

/**************************** LST_CMD_CLEAR *********************************/

void			cmdclear(t_command_lst **cmd);

/**************************** SET_REDIRECT *********************************/

char			*set_redirect(t_minishell *shell, char *block,
					t_set_fd *set_fd);
int				file_name_error(char *file_name, int *error);
char			*set_file_name(char *block, int *i);
char			*rm_redirect(char *block, int j, int i, int *error);

#endif
