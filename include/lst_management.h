/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_management.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:31:59 by judetre           #+#    #+#             */
/*   Updated: 2024/08/22 09:37:24 by judetre          ###   ########.fr       */
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

t_env	*lst_env_cpy(t_env *env);

/**************************** RETURN_ELEMENT_ENV ***************************/

t_env	*return_element_env(t_env *env, char *name);

/**************************** RETURN_VALUE_ENV ***************************/

char	*return_value_env(t_env *env, char *name);

/**************************** RETURN_VALUE_ENV ***************************/

void	remove_element_env(t_env **env, char *name);

#endif
