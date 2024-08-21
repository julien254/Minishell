/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judetre <julien.detre.dev@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 06:24:11 by judetre           #+#    #+#             */
/*   Updated: 2024/08/21 09:07:32 by judetre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MINISHELL_H
#define MINISHELL_H

# include "../libft/libft.h"
# include <stddef.h>
# include <stdlib.h>
# include "lst_management.h"
# include "env.h"

typedef struct s_minishell
{
	t_env *env;
}				t_minishell;


#endif
