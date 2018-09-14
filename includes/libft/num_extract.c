/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_extract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:37:00 by pstringe          #+#    #+#             */
/*   Updated: 2018/07/23 12:00:59 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	obtains the number's base depending on type
*/

void	get_base(t_m *m, t_num *n)
{
	if (m->place->type == 3)
		n->base = 10;
	if (m->place->type == 4)
		n->base = 10;
	if (m->place->type == 5)
		n->base = 10;
	if (m->place->type == 6)
		n->base = 8;
	if (m->place->type == 7)
		n->base = 8;
	if (m->place->type == 8 || m->place->type == 9)
		n->base = 10;
	if (m->place->type == 10)
		n->base = 16;
	if (m->place->type == 2)
		n->base = 16;
	if (m->place->type == 11)
		n->base = 16;
}

/*
**	performs propper length conversion for capital letters
*/

void	get_lmod(t_m *m)
{
	int t;

	t = m->place->type;
	m->place->len = t == 4 || t == 7 || t == 9 ? 2 : m->place->len;
}

/*
**	determines how an argument is extracted for signed conversions
*/

void	signed_conversion(t_m *m, t_num *n)
{
	if (m->place->len == -1)
		ft_spn((intmax_t)va_arg((m->ap), int), n, m);
	else if (m->place->len == 0)
		ft_spn((intmax_t)va_arg((m->ap), int), n, m);
	else if (m->place->len == 1)
		ft_spn((intmax_t)va_arg((m->ap), long long), n, m);
	else if (m->place->len == 2)
		ft_spn((intmax_t)va_arg((m->ap), long), n, m);
	else if (m->place->len == 3)
		ft_spn((intmax_t)va_arg((m->ap), int), n, m);
	else if (m->place->len == 4)
		ft_spn((intmax_t)va_arg((m->ap), intmax_t), n, m);
	else if (m->place->len == 5)
		ft_spn((intmax_t)va_arg((m->ap), size_t), n, m);
}

/*
**	determines how an argument is extracted fr unsigned conversions
*/

void	unsigned_conversion(t_m *m, t_num *n)
{
	if (m->place->len == -1)
		ft_upn((uintmax_t)va_arg((m->ap), unsigned int), n, m);
	else if (m->place->len == 0)
		ft_upn((uintmax_t)va_arg((m->ap), unsigned int), n, m);
	else if (m->place->len == 1)
		ft_upn((uintmax_t)va_arg((m->ap), unsigned long long), n, m);
	else if (m->place->len == 2)
		ft_upn((uintmax_t)va_arg((m->ap), unsigned long), n, m);
	else if (m->place->len == 3)
		ft_upn((uintmax_t)va_arg((m->ap), unsigned int), n, m);
	else if (m->place->len == 4)
		ft_upn((uintmax_t)va_arg((m->ap), uintmax_t), n, m);
	else if (m->place->len == 5)
		ft_upn((intmax_t)va_arg((m->ap), size_t), n, m);
}

/*
**	initializes the number struct needed to carry out conversion
*/

void	get_num(t_m *m, t_num *n)
{
	int type;

	n->sign = 0;
	n->idx = 0;
	ft_bzero(n->b_conv, 100);
	n->neg = 0;
	type = m->place->type;
	get_lmod(m);
	if (type == 2)
		m->place->len = 4;
	if (type == 3 || type == 4 || type == 5)
		signed_conversion(m, n);
	else if (type == 2 || type == 6 || type == 7 || type == 8 ||
			type == 10 || type == 11)
		unsigned_conversion(m, n);
}
