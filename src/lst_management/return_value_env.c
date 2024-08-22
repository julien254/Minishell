/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_value_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 08:43:41 by judetre           #+#    #+#             */
/*   Updated: 2024/08/22 09:43:15 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

char	*return_value_env(t_env *env, char *name)
{
	t_env	*elem;

	elem = return_element_env(env, name);
	return (elem->value);
}
