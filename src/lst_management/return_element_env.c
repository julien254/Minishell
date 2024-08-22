/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_element_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 08:03:25 by judetre           #+#    #+#             */
/*   Updated: 2024/08/22 08:19:55 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

t_env	*return_element_env(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
