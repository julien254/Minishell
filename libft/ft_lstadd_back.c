/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:09:19 by judetre           #+#    #+#             */
/*   Updated: 2023/11/03 17:33:58 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *neW)
{
	t_list	*last;

	if (!lst || !neW)
		return ;
	if (!(*lst))
		*lst = neW;
	else
	{
		last = ft_lstlast(*lst);
		last->next = neW;
	}
}
