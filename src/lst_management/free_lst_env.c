/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 04:09:54 by judetre           #+#    #+#             */
/*   Updated: 2024/08/26 04:25:04 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
void	free_lst_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		free(env->name);
		free(env->value);
		tmp = env->next;
		free(env);
		env = tmp;
	}
}
