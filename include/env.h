/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:54:45 by judetre           #+#    #+#             */
/*   Updated: 2024/10/01 14:21:00 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/**************************** RECOVER_ENV *********************************/

t_env	*recover_env(char **envp);
void    *set_tab_path(t_minishell *shell);

/**************************** FT_ENV *********************************/

void	print_env(t_env *env, int if_export);
void    ft_env(t_env *env);

/**************************** MAKE_TAB_ENV *********************************/

char    **make_tab_env(t_env *env);

#endif
