/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 10:09:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/07/30 19:44:03 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		swap_links(t_list *l1, t_list *l2)
{
	void		*tmp_data;
	size_t		tmp_size;

	tmp_data = l1->content;
	tmp_size = l1->content_size;
	l1->content = l2->content;
	l1->content_size = l2->content_size;
	l2->content = tmp_data;
	l2->content_size = tmp_size;
}

void			ft_lstsort(t_list *begin, int (*cmp)(void *, void *, void **, int), void **aux, int len)
{
	t_list		*link;
	int			sorted;

	if (begin == NULL)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		link = begin;
		while (link->next)
		{
			if (cmp(link->content, link->next->content, aux, len) > 0)
			{
				swap_links(link, link->next);
				sorted = 0;
			}
			link = link->next;
		}
	}
}
