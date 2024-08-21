/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_management.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:31:59 by judetre           #+#    #+#             */
/*   Updated: 2024/08/21 07:26:22 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LST_MAGEMENT_H
#define LST_MAGEMENT_H

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

void    print_env(t_env *env);
t_env	*lstlast(t_env *env);
void	lstadd_back(t_env **env, t_env *new);
t_env	*lstnew(char *name, char *value);
#endif
