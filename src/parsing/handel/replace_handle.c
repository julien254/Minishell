/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:54:57 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/01 13:21:29 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../include/minishell.h"

char	*join_without_handle(char *str, int index, int size)
{
	char	*result_str;

	result_str = (char *)malloc(sizeof(char *) * \
			(ft_strlen(str) - size + 1));
	ft_strlcpy(result_str, str, index + 1);
	str = str + index + size;
	ft_strlcat(result_str, str, index + ft_strlen(str) + 1);
	return (result_str);
}

char	*join_with_handle(char *str, int index, int size, char *value)
{
	char	*result_str;

	result_str = (char *)malloc(sizeof(char *) * \
			(ft_strlen(str) - size + ft_strlen(value) + 1));
	ft_strlcpy(result_str, str, index + 1);
	ft_strlcat(result_str, value, ft_strlen(value) + index + 1);
	str = str + index + size;
	ft_strlcat(result_str, str, ft_strlen(value) + \
			index + ft_strlen(str) + 1);
	return (result_str);
}

char	*replace_handle(char *str, int index, int size, t_env *env)
{
	char	*str_tmp;
	char	*value;
	char	*name;
	char	*result_str;

	str_tmp = ft_strdup(str);
	if (!str_tmp)
		return (NULL);
	name = str_tmp + (index + 1);
	name[size - 1] = 0;
	value = return_value_env(env, name);
	if (value)
		result_str = join_with_handle(str, index, size, value);
	else
		result_str = join_without_handle(str, index, size);
	free(str_tmp);
	free(str);
	return (result_str);
}

char	*hendles_error(char *str, int index, int exit_code)
{
	char	*str_tmp;
	char	*value;
	char	*name;
	char	*result_str;

	str_tmp = ft_strdup(str);
	if (!str_tmp)
		return (NULL);
	name = str_tmp + (index + 1);
	name[1] = 0;
	value = ft_itoa(exit_code);
	if (!value)
	{
		free(str_tmp);
		free(str);
		return (NULL);
	}
	result_str = join_with_handle(str, index, 2, value);
	free(str_tmp);
	free(str);
	return (result_str);
}
