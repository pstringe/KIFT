/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstforeach.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 10:57:57 by pstringe          #+#    #+#             */
/*   Updated: 2018/07/12 11:00:25 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstforeach(t_list *lst, void (*f)(), void **aux, int len)
{
	t_list		*tmp;

	tmp = lst;
	while (tmp)
	{
		f(tmp->content, aux, len);
		tmp = tmp->next;
	}
}
