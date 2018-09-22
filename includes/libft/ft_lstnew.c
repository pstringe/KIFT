/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 11:42:23 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/20 11:24:21 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*elem;
	void	*cpy;

	if (!(elem = (t_list *)malloc(sizeof(t_list))))
	{
		return (NULL);
	}
	elem->next = NULL;
	if (!content)
	{
		elem->content = NULL;
		elem->content_size = 0;
	}
	else
	{
		if (!(cpy = malloc(content_size)))
		{
			free(elem);
			return (NULL);
		}
		elem->content = ft_memcpy(cpy, content, content_size);
		elem->content_size = content_size;
	}
	return (elem);
}
