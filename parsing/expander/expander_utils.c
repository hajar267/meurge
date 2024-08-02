/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 01:18:26 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/02 11:55:26 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// realloc function
#include "../../minishell.h"

void *ft_realloc(void *ptr, int new_size, int len) 
{
	void	*new_ptr;

	new_ptr = NULL;
    if (ptr == NULL)
        return (malloc(new_size));
    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return (NULL);
    ft_memcpy(new_ptr, ptr, len);
    free(ptr);
    return (new_ptr);
}

char *ft_replace(char *line, int start, int end)
{
	int		len;
	char	*content;
	char	*data;
	int		i;

	i = 0;
	len = end - start + 1;
	content = malloc(len + 1);
	data = NULL;
	if (!content)
		return(NULL);
	while(start <= end)
		content[i++] = line[start++];
	content[i] = '\0';
	data = getenv(content);
	if (!data)
		return (ft_strdup(""));
	free (content);
	return (data);
}
