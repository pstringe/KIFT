/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 08:16:09 by pstringe          #+#    #+#             */
/*   Updated: 2018/07/23 12:37:14 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*extract_string(t_m *m)
{
	char *arg;

	m->place->precision = m->place->precision == -1 ? 0 : m->place->precision;
	arg = va_arg(m->ap, char*);
	arg = arg ? arg : "(null)";
	return (arg);
}

int			str(t_m *m, char buf[MAX])
{
	char	*arg;
	int		l;
	int		i;
	int		p;
	int		w;

	arg = extract_string(m);
	if (!ft_strncmp(arg, "", ((l = ft_strlen(arg)) ? l : 1)))
	{
		arg = m->place->precision ? ft_strnew(m->place->precision) : arg;
		m->place->precision = 0;
	}
	p = !m->place->precision ? ft_strlen(arg) : m->place->precision;
	w = m->place->width - p;
	i = -1;
	if (!(m->place->flags & MINUS))
		while (w-- > 0)
			buf[m->pos_b++] = ' ';
	while (arg[++i] && i < p)
		buf[m->pos_b++] = arg[i];
	if (m->place->flags & MINUS)
		while (w-- > 0)
			buf[m->pos_b++] = ' ';
	return (0);
}
