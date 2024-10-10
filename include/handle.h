/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:25:25 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/01 10:26:57 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef HANDlE_H
# define HANDlE_H

char    *replace_handle(char *str, int index, int size, t_env *env);
char    *hendles_error(char *str, int index, int exit_code);
char	*hendle_set(t_minishell *shell, char *block);

#endif /* ifndef HANDlE_H */

