/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcannaud <gcannaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:44:39 by gcannaud          #+#    #+#             */
/*   Updated: 2024/08/21 17:50:21 by gcannaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_H
# define QUOTE_H

/**************************** QUOTE_UTILS *********************************/

int				quote_error(char *s);
int				skip_quotes_while(char *str, int i);
int				skip_quotes(char *str, int i);

/**************************** QUOTE_SPLIT *********************************/

char			**quote_split(char *s);

/**************************** SPLIT_WORD *********************************/

size_t			split_word(char **s, char **tab, size_t j);

#endif