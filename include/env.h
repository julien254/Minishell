/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:54:45 by judetre           #+#    #+#             */
/*   Updated: 2024/08/26 07:43:07 by judetre          ###   ########.fr       */
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

#endif
