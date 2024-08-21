/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:37:43 by judetre           #+#    #+#             */
/*   Updated: 2024/08/21 07:59:00 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

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
