/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_element_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:20:02 by judetre           #+#    #+#             */
/*   Updated: 2024/08/26 05:47:53 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	remove_element_env(t_env **env, char *name)
{
	t_env	*current;

	if (!env || !*env)
		return ;
	current = *env;
	if (ft_strcmp(name, current->name) == 0)
	{
		*env = current->next;
		free(current);
		remove_element_env(env, name);
	}
	else
	{
		current = *env;
		remove_element_env(&current->next, name);
	}
}
