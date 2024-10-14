/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:53:59 by gcannaud          #+#    #+#             */
/*   Updated: 2024/10/14 12:19:13 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../include/minishell.h"

static int	set_hendle_size(char *block, int i)
{
	int	y;

	y = 0;
	i++;
	while (block[i] && block[i] != ' ' && block[i] != '$' && block[i] != '\''
		&& block[i] != '/' && block[i] != '"')
	{
		i++;
		y++;
	}
	return (y);
}

static char	*replace_env_var(t_minishell *shell, char *block, int i)
{
	int	y;

	y = 0;
	if (block[i + 1] == '?')
		block = hendles_error(ft_strdup(block), i, shell->exit_code);
	else
	{
		y = 1 + set_hendle_size(block, i);
		block = replace_handle(ft_strdup(block), i, y, shell->env);
	}
	return (block);
}

char	*hendle_set(t_minishell *shell, char *block)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	if (!block)
		return (NULL);
	while (block[i])
	{
		if (block[i] == '"' && k == 0)
		{
			k = 1;
			i++;
		}
		if (block[i] == '"' && k == 1)
			k = 0;
		while (block[i] == '\'' && k == 0)
			i = skip_quotes(block, i) + 1;
		if (block[i] == '$' && (block[i + 1] && block[i + 1] != ' '
				&& block[i + 1] != '$' && block[i + 1] != '\''
				&& block[i + 1] != '='
				&& block[i + 1] != '/' && block[i + 1] != '"'))
			block = replace_env_var(shell, block, i);
		else if (block[i] == '$' && k == 0 && ((block[i + 1] == '$'
				|| block[i + 1] == '\'' || block[i + 1] == '='
				|| block[i + 1] == '/' || block[i + 1] == '"')))
		{
			remove_char(&block, i);
			i--;
		}
		if (!block)
			return (NULL);
		i++;
	}
	return (block);
}
