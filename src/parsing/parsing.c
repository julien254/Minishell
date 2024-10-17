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
	while (ft_iswhitespace(shell->read[i]))
		i++;
	if (shell->read[i] == '\0')
		return (1);
	add_history(shell->read);
	return (0);
}

static int	pipe_content_error(char *s, int i)
{
	i++;
	while (ft_iswhitespace(s[i]))
		i++;
	if (s[i] == '\0' || s[i] == '|')
		return (1);
	return (0);
}

static int	pipe_error(char *s)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(s[i]))
		i++;
	if (s[i] == '|' || s[i] == ';')
		return (1);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			i = skip_quotes(s, i);
			if (i == 0)
				return (1);
		}
		if (s[i] == '|' && s[i + 1] == '|')
			return (1);
		if (s[i] == '|' && pipe_content_error(s, i))
			return (1);
		i++;
	}
	return (0);
}

static int	check_error(t_minishell *shell)
{
	if (quote_error(shell->read) || pipe_error(shell->read))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		shell->exit_code = 2;
		return (1);
	}
	return (0);
}

int	parse_command(t_minishell *shell)
{
	shell->here_doc_nbr = 1;
	if (can_be_recorded(shell))
		return (0);
	if (check_error(shell))
		return (0);
	if (!command_split(shell))
		return (1);
	if (shell->command)
		cmdclear(&shell->command);
	return (0);
}
