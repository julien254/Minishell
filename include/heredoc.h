/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:57:27 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/22 05:50:40 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

char	*set_heredoc(t_minishell *shell, t_set_fd *set_fd, char *block, int *i);
char	*here_read(char *content, char *stop);
void	write_in_term_sav(t_minishell *shell, char *and_word,
			int *heredoc_index, int *pipe_fd);

#endif
