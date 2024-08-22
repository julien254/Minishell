/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:25:51 by judetre           #+#    #+#             */
/*   Updated: 2024/08/22 11:26:36 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void    ft_export(t_env *env, char **argv)
{
	t_env *env_export;
   //	int	i;
  //	int	j;
	
	env_export = sort_list(env);
	if (!argv)
	{
		print_env(env_export, 1);
	}
}
