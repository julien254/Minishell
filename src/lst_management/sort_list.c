/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 05:56:33 by judetre           #+#    #+#             */
/*   Updated: 2024/10/14 10:10:44 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static void	swap_value(t_env **env, t_env **start, int *swap)
{
	char	*name_swap;
	char	*value_swap;

	name_swap = (*env)->name;
	value_swap = (*env)->value;
	(*env)->name = (*env)->next->name;
	(*env)->value = (*env)->next->value;
	(*env)->next->name = name_swap;
	(*env)->next->value = value_swap;
	*env = *start;
	*swap = 1;
}

static void	*swap_list(t_env **env, t_env **start, int *i, int *swap)
{
	char	*str_env;
	char	*str_env_next;

	str_env = ft_strjoin_env((*env)->name, (*env)->value);
	if (!str_env)
		return (NULL);
	str_env_next = ft_strjoin_env((*env)->next->name, (*env)->next->value);
	if (!str_env_next)
		return (NULL);
	while (str_env[*i] && str_env_next[*i])
	{
		if (str_env[*i] > str_env_next[*i])
		{
			swap_value(env, start, swap);
			break ;
		}
		else if (str_env[*i] < str_env_next[*i])
			break ;
		*i = *i + 1;
	}
	free(str_env);
	free(str_env_next);
	return ((void *)1);
}

t_env	*sort_list(t_env *env)
{
	int		swap;
	t_env	*start;
	int		i;
	void	*status;

	start = env;
	swap = 0;
	while (env != NULL && env->next != NULL)
	{
		i = 0;
		status = swap_list(&env, &start, &i, &swap);
		if (!status)
			return (NULL);
		if (!swap)
			env = env->next;
		else
			swap = 0;
	}
	return (start);
}
