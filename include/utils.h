/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:54:05 by judetre           #+#    #+#             */
/*   Updated: 2024/10/14 11:16:06 by jdetre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/wait.h>
# include <signal.h>

void		ft_free_tab(char **tab);
void		ft_sig(void);
void		ft_sig_handle(void);
int			ft_iswhitespace(char c);
char		*ft_strjoin_env(char *s1, char *s2);
long int	ft_atol_exit(const char *str);

#endif
