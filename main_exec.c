/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 22:48:19 by istili            #+#    #+#             */
/*   Updated: 2024/07/31 13:14:27 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cho(t_cmds *commands, t_link *envp, int flag)
{
	// char	*line;
	// char	**splitted;

	// line = ft_strdup_del(readline("minishell$> "));
	// splitted = ft_split(line, ' ');
	// if (line == NULL)
	// {
	// 	write(1, "minishell$> exit\n", 18);
	// 	ft_malloc_gab(0, 1);
	// 	exit(exit_status(0, 0));
	// }
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
