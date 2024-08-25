/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:25:51 by judetre           #+#    #+#             */
/*   Updated: 2024/08/25 08:20:00 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static void	*add_element_env(t_env *env, char *arg)
{
	char	**split_line_env;
	t_env	*new;
	
	split_line_env = ft_split_at_first_pattern(arg, '=');
	if (!split_line_env)
		return (NULL);
	new = lstnew(split_line_env[0], split_line_env[1]);
	lstadd_back(&env, new);
	return ((void *)1);
}

void    ft_export(t_env *env, char **argv)
{
	t_env	*env_export;
   	int		i;
	
	env_export = lst_env_cpy(env);
	sort_list(env_export);
	if (!argv)
		print_env(env_export, 1);
	else
	{
		i = 0;
		while (argv[i])
			add_element_env(env, argv[i++]);
	}
	//free env_export
}
