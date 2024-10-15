/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdetre <julien.detre.dev@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:45:47 by jdetre            #+#    #+#             */
/*   Updated: 2024/10/15 13:23:02 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static int	if_error(char *path)
{
	if (!path)
	{
		perror("minishell: cd: malloc");
		return (0);
	}
	return (1);
}

static void	update_old_path(t_minishell *shell)
{
	t_env	*old_pwd;
	char	cwd[PATH_MAX];
	int		size_path;
	char	*path;

	old_pwd = return_element_env(shell->env, "OLDPWD");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: cd:");
		return ;
	}
	size_path = ft_strlen(cwd);
	path = (char *)malloc(sizeof(char) * (size_path + 1));
	if (!path)
		return ;
	ft_strlcpy(path, cwd, size_path + 1);
	free(old_pwd->value);
	old_pwd->value = path;
}

static void	change_directory_relative(t_minishell *shell, char *path, \
		int *exit_code)
{
	char	*path_tmp;
	char	*new_path;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: cd:");
		return ;
	}
	path_tmp = ft_strjoin(cwd, "/");
	if (if_error(path_tmp) == 0)
		return ;
	new_path = ft_strjoin(path_tmp, path);
	free(path_tmp);
	if (if_error(new_path) == 0)
		return ;
	update_old_path(shell);
	if (chdir(new_path) == -1)
	{
		perror("minishell: cd");
		*exit_code = 1;
	}
	free(new_path);
}

static void	change_directory(t_minishell *shell, int argc, char **args, \
		int *exit_code)
{
	char	*path;

	if (argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		*exit_code = 1;
		return ;
	}
	path = args[1];
	if (path[0] == 0)
		return ;
	if (path[0] == '/')
	{
		update_old_path(shell);
		if (chdir(path) == -1)
		{
			perror("minishell: cd");
			*exit_code = 1;
		}
	}
	else
		change_directory_relative(shell, path, exit_code);
}

int	ft_cd(t_minishell *shell, char **args)
{
	int		size_args;
	int		exit_code;
	char	*home;

	exit_code = 0;
	size_args = ft_tab2dlen(args);
	if (size_args == 1)
	{
		home = getenv("HOME");
		if (home == NULL)
			perror("minishell: cd: HOME not set");
		else
		{
			update_old_path(shell);
			if (chdir(home) == -1)
				perror("minishell: cd");
		}
	}
	else
		change_directory(shell, size_args, args, &exit_code);
	return (exit_code);
}
