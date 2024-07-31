/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:23:47 by istili            #+#    #+#             */
/*   Updated: 2024/07/31 13:12:01 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_node(t_link *linked, t_node *node_del)
{
	if (linked->head == NULL || node_del == NULL)
		return ;
	if (linked->head == node_del)
		linked->head = node_del->next;
	if (linked->tail == node_del)
		linked->tail = node_del->prv;
	if (node_del->next != NULL)
		node_del->next->prv = node_del->prv;
	if (node_del->prv != NULL)
		node_del->prv->next = node_del->next;
}

void	f_unset(t_link *linkd, char **av)
{
	int		i;
	t_env	*env;
	t_node	*head;

	i = 1;
	while (av[i])
	{
		head = linkd->head;
		while (head)
		{
			env = head->data;
			if (!ft_strcmp(av[i], env->key))
			{
				remove_node(linkd, head);
				break ;
			}
			else
				head = head->next;
		}
		i++;
	}
}
