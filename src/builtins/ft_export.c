/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:25:51 by judetre           #+#    #+#             */
/*   Updated: 2024/10/18 13:26:17 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static int	is_valid_identifier(char *str, int *option_add)
{
	int	i;

	if (!str)
		return (0);
	if (!ft_isalpha(str[0]))
	{
		if (str[0] != '_')
			return (0);
	}
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
		{
			if (str[i] != '_' && !(str[i + 1] == 0 && str[i] == '+'))
				return (0);
		}
		i++;
	}
	if (str[i - 1] == '+')
	{
		str[i - 1] = 0;
		*option_add = 1;
	}
	return (1);
}

void	update_element(t_env *env, int *option_add, char **split)
{
	char	*value_tmp;

	if (*option_add)
	{
		value_tmp = ft_strjoin(env->value, split[1]);
		free(env->value);
		ft_free_malloc2d((void *)split);
		env->value = value_tmp;
	}
	else
	{
		free(split[0]);
		free(env->value);
		env->value = split[1];
		free(split);
	}
}

static void	*add_element_env(t_minishell *shell, char *arg, int *option_add)
{
	char	**split_line_env;
	t_env	*new;

	split_line_env = ft_split_at_first_pattern(arg, '=');
	if (!split_line_env)
		return (NULL);
	if (!is_valid_identifier(split_line_env[0], option_add))
	{
		ft_free_malloc2d((void *)split_line_env);
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		shell->exit_code = 1;
		return (NULL);
	}
	new = return_element_env(shell->env, split_line_env[0]);
	if (!new)
	{
		new = lstnew(split_line_env[0], split_line_env[1]);
		free(split_line_env);
		lstadd_back(&shell->env, new);
	}
	else
		update_element(new, option_add, split_line_env);
	return ((void *)1);
}

void	ft_export(t_minishell *shell, char **argv)
{
	t_env	*env_export;
	int		option_add;
	int		i;

	option_add = 0;
	if (ft_tab2dlen(argv) == 1)
	{
		env_export = lst_env_cpy(shell->env);
		sort_list(env_export);
		print_env(env_export, 1);
		free_lst_env(env_export);
	}
	else
	{
		i = 1;
		while (argv[i])
		{
			add_element_env(shell, argv[i++], &option_add);
		}
	}
}
