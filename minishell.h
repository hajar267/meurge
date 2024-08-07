/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:25:27 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/07 10:29:05 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "execution.h"
#include "parsing/parsing.h"

void	cho(t_cmds *commands, t_link *envp, int flag);
char	*find_val(t_link *envp, char *key);
#endif