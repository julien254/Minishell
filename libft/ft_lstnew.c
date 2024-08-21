/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:07:04 by judetre           #+#    #+#             */
/*   Updated: 2023/11/03 17:32:49 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = (t_list *)ft_calloc(sizeof(t_list), 1);
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
