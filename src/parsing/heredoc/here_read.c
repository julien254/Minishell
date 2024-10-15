/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:59:39 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/21 18:03:44 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../include/minishell.h"

static char	*process_line(char *content, char *line, char *stop)
{
	char	*tmp;

	tmp = NULL;
	if (content)
	{
		tmp = ft_strjoin(content, "\n");
		free(content);
		content = tmp;
	}
	else
		content = ft_calloc(1, 1);
	if (ft_strncmp(line, stop, (ft_strlen(stop) + 1)) != 0)
	{
		tmp = ft_strjoin(content, line);
		free(content);
		content = tmp;
	}
	return (content);
}

static void	exit_here(char *line, char *tmp, char *content)
{
	free(line);
	free(tmp);
	free(content);
}

static int	check_stop_condition(char *tmp, char *stop)
{
	if ((tmp == NULL || (ft_strncmp(tmp, stop, (ft_strlen(stop) + 1)) != 0)))
		return (0);
	return (1);
}

char	*here_read(char *content, char *stop)
{
	char	*tmp;
	char	*line;

	tmp = NULL;
	line = NULL;
	while (!check_stop_condition(tmp, stop))
	{
		line = readline("> ");
		if ((!line && g_signal == 0) || g_signal == 1)
		{
			exit_here(line, tmp, content);
			return (NULL);
		}
		if (line != tmp)
		{
			content = process_line(content, line, stop);
			free(tmp);
			tmp = ft_strdup(line);
		}
		free(line);
	}
	free (tmp);
	return (content);
}
