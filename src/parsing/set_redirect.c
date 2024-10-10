/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:59:39 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/21 18:03:44 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

char	*rm_redirect(char *block, int j, int i, int *error)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(block, 0, j);
	tmp2 = ft_substr(block, i, ft_strlen(block) - i);
	tmp3 = ft_strjoin(tmp, tmp2);
	if (!tmp3)
	{
		if (tmp)
			free(tmp);
		if (tmp2)
			free(tmp2);
		*error = 1;
		return (NULL);
	}
	free(tmp);
	free(tmp2);
	free(block);
	return (tmp3);
}

int	file_name_error(char *file_name, int *error)
{
	if (!file_name)
	{
		*error = 1;
		return (1);
	}
	if (file_name[0] == '\0')
	{
		free(file_name);
		return (1);
	}
	return (0);
}

static char	*set_redirect_in(char *block, int *i, int *fd_in, int *error)
{
	char	*file_name;
	int		j;

	j = *i;
	file_name = set_file_name(block, i);
	if (file_name_error(file_name, error))
		return (NULL);
	*fd_in = open(file_name, O_RDONLY);
	/*if (*fd_in == -1)
	{
		printf("minishell: %s: No such file or directory\n", file_name);
		//free(file_name);
		//return (NULL);
	}*/
	free(file_name);
	
	block = rm_redirect(block, j, *i, error);
	*i = j - 1;
	return (block);
}

static char	*set_redirect_out(char *block, int *i, int *fd_out, int *error)
{
	char	*file_name;
	int		j;

	j = *i;
	file_name = set_file_name(block, i);
	if (file_name_error(file_name, error))
		return (NULL);
	(*i)++;
	if (block[*i] == '>')
		*fd_out = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		*fd_out = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	/*if (*fd_out == -1)
	{
		printf("minishell: %s: No such file or directory\n", file_name);
		//free(file_name);
		*error = 0;
		//return (NULL);
	}*/
	free(file_name);
	block = rm_redirect(block, j, *i - 1, error);
	*i = j - 1;
	return (block);
}

char	*set_redirect(t_minishell *shell, char *block, t_set_fd *set_fd)
{
	int	i;

	i = 0;
	set_fd->heredoc_index = 0;
	if (!block)
		return (NULL);
	while (block[i])
	{
		i = skip_quotes_while(block, i);
		if (block[i] == '>')
			block = set_redirect_out(block, &i, &set_fd->fd_out,
					&set_fd->error);
		else if (block[i] == '<' && block[i + 1] != '<')
			block = set_redirect_in(block, &i, &set_fd->fd_in, &set_fd->error);
		else if (!ft_strncmp(&block[i], "<<", 1))
			block = set_heredoc(shell, set_fd, block, &i);
		if (!block)
			return (NULL);
		i++;
	}
	return (block);
}
