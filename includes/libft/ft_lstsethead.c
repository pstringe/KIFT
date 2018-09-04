/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsethead.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 17:42:32 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/22 17:48:53 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	**ft_lstsethead(t_list *elem)
{
	t_list	**head;

	head = NULL;
	if (elem)
	{
		*head = elem;
		return (head);
	}
	free(head);
	return (NULL);
}
