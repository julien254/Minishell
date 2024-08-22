/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_cpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 06:49:34 by judetre           #+#    #+#             */
/*   Updated: 2024/08/22 07:32:46 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

t_env	*lst_env_cpy(t_env *env)
{
	t_env	*cpy;
	t_env	*new;
	char	*name;
	char	*value;

	cpy = NULL;
	while (env)
	{
		name = ft_strdup(env->name);
		value = ft_strdup(env->value);
		new = lstnew(name, value);
		lstadd_back(&cpy, new);
		env = env->next;
	}
	return (cpy);
}
