/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:59:39 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/21 18:03:44 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../include/minishell.h"

static void	ft_fillsave(char *content, char *name)
{
	int	fd;

	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	ft_putstr_fd(content, fd);
	close(fd);
}

static void	write_in_term_sav(t_minishell *shell, char *and_word,
			int heredoc_index)
{
	char	*tmp_name;
	char	*content;

	(void)shell;
	content = NULL;
	ft_sig_handle();
	content = here_read(content, and_word);
	if (content == NULL)
		exit(0);
	tmp_name = ft_strjoin("test", ft_itoa(heredoc_index));
	ft_fillsave(content, tmp_name);
	free(tmp_name);
	free(content);
	exit(130);
}

char	*set_heredoc(t_minishell *shell, t_set_fd *set_fd, char *block,
		int *i)
{
	char	*file_name;
	pid_t	pid;
	int		status;
	int		exit_code;
	int		j;

	exit_code = 0;
	pid = 0;
	j = *i;
	file_name = set_file_name(block, i);
	if (!file_name)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (block);
	set_fd->heredoc_index = shell->here_doc_nbr;
	if (pid == 0)
		write_in_term_sav(shell, file_name, set_fd->heredoc_index);
	shell->here_doc_nbr += 1;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	if (exit_code == 0)
		return (NULL);
	block = rm_redirect(block, j, *i);
	return (block);
}
