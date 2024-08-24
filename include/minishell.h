/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:24:11 by judetre           #+#    #+#             */
/*   Updated: 2024/08/22 10:25:23 by judetre          ###   ########.fr       */
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
# include "env.h"
# include "utils.h"
# include "export.h"
# include "minishell_struct.h"
# include "parsing.h"
# include "heredoc.h"
# include "quote.h"

extern int	g_signal;

void	parse_command(t_minishell *shell);
void	command_split(t_minishell *shell);

#endif
