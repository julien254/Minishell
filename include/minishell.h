/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:24:11 by judetre           #+#    #+#             */
/*   Updated: 2024/08/21 17:44:47 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "lst_management.h"
# include "env.h"
# include "utils.h"
# include "parsing.h"
# include "quote.h"

extern int	g_signal;

typedef struct s_minishell
{
	t_env			*env;
	t_command_lst	*command;
	char			*read;
	int 			exit_code;
}				t_minishell;

void	parse_command(t_minishell *shell);
void	command_split(t_minishell *shell);

#endif
