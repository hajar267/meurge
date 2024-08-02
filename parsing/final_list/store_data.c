/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 03:36:57 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/02 22:00:41 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmds	*last_node(t_cmds *data)
{
	if (!data)
		return (NULL);
	while (data->next)
		data = data->next;
	return (data);
}

void	add_nod(t_cmds **token, t_cmds *data)
{
	t_cmds	*nod;

	if (!(*token))
	{
		(*token) = data;
		return ;
	}
	nod = last_node((*token));
	nod->next = data;
	data->prev = nod;
	data->next = NULL;
}

t_cmds	*new_node(int i)
{
	t_cmds	*node;

	node = ft_malloc_gab(sizeof(t_cmds), 0);
	node->data = ft_malloc_gab(sizeof(char *) * (i + 1), 0);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	store_data(t_cmds	**cmd, t_token	*token)
{
	int		j;
	t_cmds	*last;

	j = 0;
	last = last_node(*cmd);
	while (token->data[j])
	{
		last->data[j] = ft_strdup(token->data[j]);
		j++;
	}
	last->data[j] = NULL;
}

void	convert_to_new_list(t_token *token, t_cmds **cmnd)
{
	t_token	*command;
	t_token	*head;
	t_cmds	*tmp;
	int		i;
	int		len;

	command = ft_new_list(token);
	head = command;
	while (head)
	{
		//if i want to open the fds directly in tokens -->
		// if (head->type == REDIRECT_IN || head->type == REDIRECT_OUT)
		// 	head = head->next->next;
		// ft_open_files(head->prev);
		if (!head)
			break;
		len = ft_len_args(head->data);
		tmp = new_node(len);
		add_nod(cmnd, tmp);
		store_data(cmnd, head);
		i = 0;
		while (head->data[i])
			i++;
		head = head->next;
	}
}
