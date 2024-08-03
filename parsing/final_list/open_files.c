/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:45:03 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/03 21:42:10 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_red_out(t_cmds *command)
{
	command->fd = open(command->next->data[0], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (command->fd == -1)
	{
		printf("failed to open\n");
		ft_malloc_gab(0, 1);
		return (-1);
	}
	write(command->fd,"red\n",4);
	close (command->fd);
	return (1);
}

int	ft_append(t_cmds *command)
{
	command->fd = open(command->next->data[0], O_RDWR | O_CREAT | O_APPEND , S_IRUSR | S_IWUSR);
	if (command->fd == -1)
	{
		printf("failed to open\n");
		ft_malloc_gab(0, 1);
		return (-1);
	}
	write(command->fd,"n >\n",4);
	close (command->fd);
	return (1);
}

int ft_red_in(t_cmds *command)
{
	if (access(command->next->data[0], F_OK) == 0)
	{
		command->fd = open(command->next->data[0], O_RDWR , S_IRUSR | S_IWUSR);
		if (command->fd == -1)
		{
			printf("failed to open\n");
			return (-1);
		}
		write(command->fd,"h",1);
		close (command->fd);
	}
	else
	{
		printf("NO such file or directory\n");
		return (-1);
	}
	return (1);
}

int	ft_open_files(t_cmds	*command)
{
	while(command)
	{
		if (ft_strcmp(command->data[0], ">") == 0)
		{
			if (ft_red_out(command) == -1)
				return (-1);
		}
		else if (ft_strcmp(command->data[0], ">>") == 0)
		{
			if (ft_append(command) == -1)
				return (-1);
		}
		else if (ft_strncmp(command->data[0], "<", 1) == 0)
		{
			if (ft_red_in(command) == -1)
				return (-1);
		}
		command = command->next;
	}
	return (1);
}
