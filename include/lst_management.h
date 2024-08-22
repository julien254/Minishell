/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_management.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:31:59 by judetre           #+#    #+#             */
/*   Updated: 2024/08/22 06:57:51 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LST_MANAGEMENT_H
# define LST_MANAGEMENT_H

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

/**************************** LST_ENV_UTILS *********************************/
t_env	*sort_list(t_env *env);
t_env	*lstlast(t_env *env);
void	lstadd_back(t_env **env, t_env *new);
t_env	*lstnew(char *name, char *value);

/**************************** LST_ENV_CPY *********************************/

t_env   *lst_env_cpy(t_env *env);

#endif
