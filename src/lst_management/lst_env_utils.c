/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:37:43 by judetre           #+#    #+#             */
/*   Updated: 2024/08/22 06:05:15 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static void	swap_list(t_env **env, t_env **start, int *i, int *swap)
{
	char	*name_swap;
	char	*value_swap;

	while ((*env)->name[*i] && (*env)->next->name[*i])
	{
		if ((*env)->name[*i] > (*env)->next->name[*i])
		{
			name_swap = (*env)->name;
			value_swap = (*env)->value;
			(*env)->name = (*env)->next->name;
			(*env)->value = (*env)->next->value;
			(*env)->next->name = name_swap;
			(*env)->next->value = value_swap;
			*env = *start;
			*swap = 1;
			break ;
		}
		else if ((*env)->name[*i] < (*env)->next->name[*i])
			break ;
		*i = *i + 1;
	}
}

t_env	*sort_list(t_env *env)
{
	int		swap;
	t_env	*start;
	int		i;

	start = env;
	swap = 0;
	while (env != NULL && env->next != NULL)
	{
		i = 0;
		swap_list(&env, &start, &i, &swap);
		if (!swap)
			env = env->next;
		else
			swap = 0;
	}
	return (start);
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
