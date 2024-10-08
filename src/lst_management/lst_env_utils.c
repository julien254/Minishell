/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:37:43 by judetre           #+#    #+#             */
/*   Updated: 2024/10/08 10:19:59 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

t_env	*lstlast(t_env *env)
{
	while (env)
	{
		if (env->next == NULL)
			return (env);
		env = env->next;
	}
	return (0);
}

void	lstadd_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (!(*env))
		*env = new;
	else
	{
		last = lstlast(*env);
		last->next = new;
	}
}

t_env	*lstnew(char *name, char *value)
{
	t_env	*lst;

	lst = (t_env *)malloc(sizeof(t_env));
	//if (!lst)
	//fonction pour quitter proprement
	lst->name = name;
	lst->value = value;
	lst->next = NULL;
	return (lst);
}
