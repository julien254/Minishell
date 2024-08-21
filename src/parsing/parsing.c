/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:57:27 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/21 15:56:05 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static int	can_be_recorded(t_minishell *shell)
{
	int	i;

	i = 0;
	while(ft_iswhitespace(shell->read[i]))
		i++;
	if (shell->read[i] == '\0')
		return (1);
	add_history(shell->read);
	return (0);
}

void	parse_command(t_minishell *shell)
{
	if (can_be_recorded(shell))
		return ;
	command_split(shell);
}
