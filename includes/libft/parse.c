/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:45:41 by pstringe          #+#    #+#             */
/*   Updated: 2018/07/23 12:30:34 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define S_W_N (m->format[m->pos_f + 1]>='0'&&m->format[m->pos_f + 1]<='9')
#define I_P m->format[m->pos_f]=='%'
#define I_W m->format[m->pos_f]== '*'
#define N_P ((I_P || I_W || m->format[m->pos_f]=='.') ? m->pos_f+1 : m->pos_f)

/*
**	checks for width parameter in placeholder or wildcard, and stores
*/

int		get_width(t_m *m)
{
	int l;
	int a;
	int s;
	int w;

	s = m->place->flags & SPACE ? 0 : 1;
	skip_whitespace(m);
	m->place->width = 0;
	if ((a = (m->format[m->pos_f + s] == '*')))
		m->place->width = va_arg(m->ap, int);
	else if (m->format[m->pos_f + s] >= '0' && m->format[m->pos_f + s] <= '9')
		m->place->width = ft_atoi(m->format + m->pos_f + s);
	else
		return (0);
	l = 1;
	w = m->place->width;
	while ((w /= 10) && !a)
		l++;
	m->pos_f += l;
	skip_whitespace(m);
	return (l);
}

/*
**	checks for flag and stores
*/

int		get_flags(t_m *m)
{
	int	f;
	int	i;
	int a;

	a = m->format[m->pos_f] == '%' ? 1 : 0;
	i = -1;
	while ((f = is_flag(m->format[m->pos_f + a])))
	{
		m->place->flags |= (1 << (f - 1));
		m->pos_f++;
	}
	return (1);
}

/*
**	checks for precision parameter or wildcard and stores
*/

int		get_precision(t_m *m)
{
	int	p;
	int	l;

	if (m->format[m->pos_f] == '.')
		m->pos_f--;
	if (m->format[m->pos_f + 1] == '.')
		if (m->format[++m->pos_f + 1] == '*')
		{
			m->place->precision = va_arg(m->ap, int);
			m->pos_f++;
		}
		else if (S_W_N)
			m->place->precision = ft_atoi(m->format + m->pos_f + 1);
		else
			return (-1);
	else
		m->place->precision = -1;
	l = 1;
	p = m->place->precision;
	while (p >= 0 && (p /= 10))
		l++;
	m->pos_f += m->place->precision == -1 ? 0 : l;
	return (l);
}

/*
**	checks for length modifier and stores
*/

int		get_len(t_m *m)
{
	char	*lens[NO_OF_LENS];
	int		i;
	int		l;

	init_lens(lens);
	i = -1;
	while (++i < NO_OF_LENS && m->place->len < 0)
		if (!ft_strncmp(m->format + m->pos_f + 1, lens[i],
					(l = ft_strlen(lens[i]))))
			m->place->len = i;
		else
			l = 0;
	if ((I_P && m->place->start != m->pos_f) ||
			(m->place->len == -1 && (m->place->flags & SPACE)))
		m->pos_f += 0;
	else
		m->pos_f += l + 1;
	return (l);
}

/*
**	checks for type and stores
*/

int		get_type(t_m *m)
{
	char	*types;
	int		i;

	types = TYPES;
	if (I_P && m->place->start != m->pos_f)
	{
		m->place->type = 14;
		return (1);
	}
	m->pos_f = N_P;
	if (!(I_W || I_P))
		while (m->format[m->pos_f] >= '0' && m->format[m->pos_f] <= '9')
			m->pos_f++;
	i = -1;
	while (types[++i])
		if (m->format[m->pos_f] == types[i])
			m->place->type = i;
	if (m->place->type == 0 && m->place->len == 2)
		m->place->type = 1;
	m->pos_f++;
	return (i);
}
