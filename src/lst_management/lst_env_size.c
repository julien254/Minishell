/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:05:21 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/01 14:07:28 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	lst_env_size(t_env *env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}
