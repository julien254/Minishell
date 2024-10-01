/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:54:57 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/01 11:05:10 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

char	*replace_handle(char *str, int index, int size, t_env *env)
{
	char	*str_tmp;
	char	*value;
	char	*name;
	char	*result_str;
	char	*str_residu;
	
	str_tmp = ft_strdup(str);
	name = str_tmp + (index + 1);
	name[size - 1] = 0;
	value = return_value_env(env, name);
	result_str = (char *)malloc(sizeof(char *) * \
			(ft_strlen(str) - size + ft_strlen(value) + 1));
	ft_strlcpy(result_str, str_tmp, index + 1);
	ft_strlcat(result_str, value, ft_strlen(value) + index + 1);
	str_residu = str + index + size;
	ft_strlcat(result_str, str_residu, ft_strlen(value) + \
			index + ft_strlen(str_residu) + 1);
	ft_printf("%s", result_str); // a supprimer, cest pour l'exemple. 
	free(str_tmp);
	free(str);
	return (result_str);
}
