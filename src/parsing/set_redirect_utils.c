/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:57:27 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/21 15:56:05 by gcannaud         ###   ########.fr       */
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

char	*handle_file_name_error(char *file_name, char *block,
	t_set_fd *set_fd)
{
	if (file_name_error(file_name, &set_fd->error))
	{
		if (block)
			free(block);
		return (NULL);
	}
	return (file_name);
}
