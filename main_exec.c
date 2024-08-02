/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 22:48:19 by istili            #+#    #+#             */
/*   Updated: 2024/08/02 21:36:08 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cho(t_cmds *commands, t_link *envp, int flag)
{
	if (!ft_strcmp(commands->data[0], "export"))
		f_export(envp, commands->data, flag);
	else if (!ft_strcmp(commands->data[0], "env"))
		f_env(envp);
	else if (!ft_strcmp(commands->data[0], "exit"))
		f_exit(commands->data);
	else if (!ft_strcmp(commands->data[0], "echo"))
		f_echo(commands->data);
	else if (!ft_strcmp(commands->data[0], "pwd"))
		f_pwd(envp);
	else if (!ft_strcmp(commands->data[0], "unset"))
		f_unset(envp, commands->data);
	else if (!ft_strcmp(commands->data[0], "cd"))
		f_cd(commands->data, envp);
	else
		printf("minishell: %s: command not found\n", commands->data[0]); // execution
}
