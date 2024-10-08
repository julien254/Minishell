/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 05:44:47 by judetre           #+#    #+#             */
/*   Updated: 2024/10/08 10:29:23 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

char	*ft_strjoin_env(char *s1, char *s2)
{
	char	*str;

	if (!s1)
		return (NULL);
	if (!s2)
	{
		str = ft_strdup(s1);
		return (str);
	}
	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 2, 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, "=", (ft_strlen(s1) + 2));
	ft_strlcat(str, s2, (ft_strlen(s1) + ft_strlen(s2) + 2));
	return (str);
}
