/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:24:11 by judetre           #+#    #+#             */
/*   Updated: 2024/08/26 07:46:44 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "lst_management.h"
# include "minishell_struct.h"
# include "env.h"
# include "utils.h"
# include "export.h"
# include "parsing.h"
# include "heredoc.h"
# include "quote.h"
# include "exit.h"
# include "unset.h"
# include "exec.h"

extern int	g_signal;

int		parse_command(t_minishell *shell);
int		command_split(t_minishell *shell);

#endif
