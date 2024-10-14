/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 07:28:52 by judetre           #+#    #+#             */
/*   Updated: 2024/10/14 10:50:03 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXEC_H
# define EXEC_H
# include <sys/stat.h>
# include <errno.h>

void	exec_cmd(t_minishell *shell);

#endif
