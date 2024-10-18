/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 07:28:52 by judetre           #+#    #+#             */
/*   Updated: 2024/10/18 15:46:54 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXEC_H
# define EXEC_H
# include <sys/stat.h>
# include <errno.h>

/*********************************** FT_EXEC **************************/

void	exec_cmd(t_minishell *shell);

/******************************** EXEC_BUILTINS ***********************/

int		if_is_builtins_exec_in_parent(t_minishell *shell);
int		if_is_builtins(t_minishell *shell);
int		exec_builtins(t_minishell *shell, int exit_option);

/******************************** EXEC_ERR ****************************/

void	check_err_command(t_minishell *shell);
void	putstr_err_command(t_minishell *shell);

/***************************** EXEC_DUP2_UTILS ************************/

void	ft_choose_dup2(t_minishell *shell, char *order);
void	ft_choose_dup2_with_no_pipe(t_minishell *shell);

/***************************** EXEC_UTILS ************************/

pid_t	ft_fork(void);
void	ft_pipe(t_minishell *shell);
void	set_exit_code(t_minishell *shell, int status);
int		if_backslash(char *str);
int		is_directory(t_minishell *shell);

/***************************** EXEC_PATH_UTILS ************************/

char	*ft_recovery_cmd(t_minishell *shell, size_t i);

/***************************** EXEC_HEREDOC ************************/

void	if_heredoc(t_minishell *shell);

/***************************** EXEC_HEREDOC ************************/

void	close_all_fd(t_command_lst *lst_command);

/***************************** EXEC_HEREDOC ************************/

void	print_invalid_perm(t_minishell *shell);
void	print_no_file(t_minishell *shell);

#endif
