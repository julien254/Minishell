/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:45:47 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/09 13:56:45 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void change_directory_relative(char *path) 
{
	char	*path_tmp;
	char	*new_path;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: cd:");
		return;
	}
	path_tmp = ft_strjoin(cwd, "/");
	if (!path_tmp)
	{
		perror("minishell: cd: malloc");
		return ;
	}
	new_path = ft_strjoin(path_tmp, path);
	free(path_tmp);
	if (!new_path)
	{
		perror("minishell: cd: malloc");
		return ;
	}
	if (chdir(new_path) == -1)
		perror("minishell: cd");	
	free(new_path);
}

void change_directory(int argc, char **args) 
{
	char	*path;

	if (argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return;
	}
	path = args[1];
	if (path[0] == 0)
		return ;
	if (path[0] == '/')
	{
		if (chdir(path) == -1)
			perror("minishell: cd");
	}
	else
		change_directory_relative(path);
}

void ft_cd(char **args)
{	
	int	size_args;
	char	*home;

	size_args = ft_tab2dlen(args);
	if (size_args == 1) 
	{
        home = getenv("HOME");
        if (home == NULL)
            perror("minishell: cd: HOME not set");
		else
		{
           if (chdir(home) == -1)
			perror("minishell: cd");
		}
    }
	else
        change_directory(size_args, args);
}

