/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 08:25:56 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/16 18:28:27 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_queue		*ft_queuenw(void *n, size_t size)
{
	t_queue	*q;
	t_list	*tmp;

	q = (t_queue*)ft_memalloc(sizeof(t_queue));
	tmp = ft_lstnew(n, size);
	q->tail = tmp;
	q->head = tmp;
	return (q);
}

void		ft_enqueue(struct s_queue *q, void *n, size_t size)
{
	t_list	*tmp;

	tmp = ft_lstnew(n, size);
	if (!q->tail)
	{
		q->tail = tmp;
		q->head = tmp;
		return ;
	}
	q->tail->next = tmp;
	q->tail = tmp;
}

void		*ft_dequeue(struct s_queue *q)
{
	t_list		*tmp;
	void		*t;

	if (!q->head)
		return (NULL);
	tmp = q->head;
	q->head = tmp->next;
	t = ft_memalloc(tmp->content_size);
	ft_memcpy(t, tmp->content, tmp->content_size);
	ft_memdel((void**)&(tmp->content));
	ft_memdel((void**)&tmp);
	if (!q->head)
		q->tail = NULL;
	return (t);
}
