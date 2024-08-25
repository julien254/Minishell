/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:54:05 by judetre           #+#    #+#             */
/*   Updated: 2024/08/25 05:55:39 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/wait.h>
# include <signal.h>

void	ft_free_tab(char **tab);
void	ft_sig(void);
int		ft_iswhitespace(char c);
char    *ft_strjoin_env(char *s1, char *s2);

#endif
