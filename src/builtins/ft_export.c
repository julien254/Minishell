/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:25:51 by judetre           #+#    #+#             */
/*   Updated: 2024/10/05 08:20:11 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"
static int	is_valid_identifier(char *str)
{
	int i;

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
			if (str[i] != '_')
				return (0);
		}
		i++;
	}
	return (1);
}

static void	*add_element_env(t_env *env, char *arg)
{
	char	**split_line_env;
	t_env	*new;
	
	split_line_env = ft_split_at_first_pattern(arg, '=');
	if (!split_line_env)
		return (NULL);
	if (!is_valid_identifier(split_line_env[0]))
	{
		ft_free_malloc2d((void *)split_line_env);
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (NULL);
	}
	new = lstnew(split_line_env[0], split_line_env[1]);
	lstadd_back(&env, new);
	return ((void *)1);
}

void    ft_export(t_env *env, char **argv)
{
	t_env	*env_export;
   	int		i;
	
	if (ft_tab2dlen(argv) == 1)
	{
		env_export = lst_env_cpy(env);
		sort_list(env_export);
		print_env(env_export, 1);
		free_lst_env(env_export);
	}
	else
	{
		i = 1;
		while (argv[i])
			add_element_env(env, argv[i++]);
	}
}
