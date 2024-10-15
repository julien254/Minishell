/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:53:50 by judetre           #+#    #+#             */
/*   Updated: 2024/10/15 13:42:21 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	*set_tab_path(t_minishell *shell)
{
	char	*path;
	char	**tab_path;

	path = return_value_env(shell->env, "PATH");
	tab_path = ft_split(path, ':');
	if (!tab_path)
		return (NULL);
	return (tab_path);
}

t_env	*recover_env(char **envp)
{
	int		i;
	t_env	*env;
	t_env	*new;
	char	**split_line_env;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		split_line_env = ft_split_at_first_pattern(envp[i], '=');
		if (!split_line_env)
			return (NULL);
		new = lstnew(split_line_env[0], split_line_env[1]);
		free(split_line_env);
		lstadd_back(&env, new);
		i++;
	}
	return (env);
}
