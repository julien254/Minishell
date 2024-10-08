/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:15:53 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/08 12:23:55 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef BUILTINS_H
# define BUILTINS_H
# include <limits.h>

void    ft_env(t_env *env);
void    print_env(t_env *env, int if_export);
int		ft_exit(t_minishell *shell, int exec_option);
void    ft_export(t_env *env, char **argv);
void    ft_pwd(void);
void	ft_unset(t_minishell *shell, char **name);
void	ft_echo(t_minishell *shell, char **args);
void	ft_cd(char **args);

#endif

