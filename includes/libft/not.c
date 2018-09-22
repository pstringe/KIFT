/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 07:36:36 by pstringe          #+#    #+#             */
/*   Updated: 2018/06/13 16:34:20 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		not(t_m *m, char buf[MAX])
{
	int		p;
	int		w;

	m->place->precision = m->place->precision == -1 ? 0 : m->place->precision;
	p = !m->place->precision ? 1 : m->place->precision;
	w = m->place->width - p;
	if (!(m->place->flags & MINUS))
		while (w-- > 0)
			buf[m->pos_b++] = ' ';
	buf[m->pos_b++] = '%';
	if (m->place->flags & MINUS)
		while (w-- > 0)
			buf[m->pos_b++] = ' ';
	return (0);
}
