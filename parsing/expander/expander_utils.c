/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 01:18:26 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/07 18:00:25 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// realloc function
#include "../../minishell.h"

void	*ft_realloc(void *ptr, int new_size, int len)
{
	void	*new_ptr;

	new_ptr = NULL;
    if (ptr == NULL)
        return (ft_malloc_gab(new_size, 0));
    new_ptr = ft_malloc_gab(new_size, 0);
    ft_memcpy(new_ptr, ptr, len);
    return (new_ptr);
}

char	*ft_replace(char *line, int start, int end, t_link *envp)
{
	int		len;
	char	*content;
	char	*data;
	int		i;

	i = 0;
	len = end - start + 1;
	content = ft_malloc_gab(len + 1, 0);
	data = NULL;
	while(start <= end)
		content[i++] = line[start++];
	content[i] = '\0';
	data = find_val(envp, content);
	if (!data)
		return (ft_strdup(""));
	return (data);
}
