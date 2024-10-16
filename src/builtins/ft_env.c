/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 05:54:16 by judetre           #+#    #+#             */
/*   Updated: 2024/10/16 16:21:14 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

/* if_export is an option to know if the function should print with */
/* env or export : 0 = print_env, 1 = print_export*/
void	print_env(t_env *env, int if_export)
{
	if (!if_export)
	{
		while (env)
		{
			if (env->value)
				printf("%s=%s\n", env->name, env->value);
			env = env->next;
		}
	}
	else
	{
		while (env)
		{
			if (ft_strcmp(env->name, "_") != 0)
			{
				printf("declare -x ");
				if (env->value)
					printf("%s=\"%s\"\n", env->name, env->value);
				else
					printf("%s\n", env->name);
			}
			env = env->next;
		}
	}
}

void	ft_env(t_env *env)
{
	print_env(env, 0);
}
