/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdstry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 10:50:51 by pstringe          #+#    #+#             */
/*   Updated: 2018/07/28 20:44:24 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	def(t_list *node)
{
	ft_memdel((void**)&node->content);
	node->content_size = 0;
	ft_memdel((void**)&node);
}

void		ft_lstdstry(t_list **lst, void (*des)(t_list*))
{
	t_list *tmp;
	t_list *next;

	if (!des)
		des = def;
	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;
		des(tmp);
		tmp = next;
	}
	*lst = NULL;
}
