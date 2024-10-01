/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tab_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:50:29 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/01 14:46:30 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

char	**make_tab_env(t_env *env)
{
	int		size;
	int		i;
	char	**tab_env;

	size = lst_env_size(env);
	tab_env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tab_env)
		return (NULL);
	i = 0;
	while (env)
	{
		tab_env[i] = ft_strjoin_env(env->name, env->value);
		if (!tab_env[i])
		{
			ft_free_malloc2d((void *)tab_env);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	tab_env[i] = NULL;
	return (tab_env);
}
