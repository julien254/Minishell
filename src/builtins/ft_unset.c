/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 05:43:54 by judetre           #+#    #+#             */
/*   Updated: 2024/10/14 10:32:53 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	ft_unset(t_minishell *shell, char **name)
{
	int	i;

	i = 1;
	while (name[i])
		remove_element_env(&shell->env, name[i++]);
	shell->exit_code = 0;
}
