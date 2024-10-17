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

static int	set_handle_size(char *block, int i)
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
	int		y;
	char	*tmp;

	y = 0;
	if (block[i + 1] == '?')
	{
		tmp = ft_strdup(block);
		free(block);
		block = handles_error(tmp, i, shell->exit_code);
	}
	else
	{
		y = 1 + set_handle_size(block, i);
		tmp = ft_strdup(block);
		free(block);
		block = replace_handle(tmp, i, y, shell->env);
	}
	return (block);
}

static void	quotes_skip(char *block, int *i, int *k)
{
	if (block[*i] == '"' && *k == 0)
	{
		*k = 1;
		(*i)++;
	}
	if (block[*i] == '"' && *k == 1)
		*k = 0;
	while (block[*i] == '\'' && *k == 0)
		*i = skip_quotes(block, *i) + 1;
}

char	*handle_set(t_minishell *shell, char *block)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	while (block && block[i])
	{
		quotes_skip(block, &i, &k);
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
		else
			i++;
		if (!block)
			return (NULL);
	}
	return (block);
}
