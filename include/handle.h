/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:25:25 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/14 10:52:28 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef HANDLE_H
# define HANDLE_H

char	*replace_handle(char *str, int index, int size, t_env *env);
char	*handles_error(char *str, int index, int exit_code);
char	*handle_set(t_minishell *shell, char *block);
void	remove_char(char **s, size_t i);

#endif
