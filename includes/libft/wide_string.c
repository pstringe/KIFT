/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wide_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:01:16 by pstringe          #+#    #+#             */
/*   Updated: 2018/07/23 13:22:52 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_wstrncmp(const wchar_t *s1, const wchar_t *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (*(s1 + i) == *(s2 + i) && *(s1 + i) && i < n)
		i++;
	if (i == n)
		return (*(s1 + i - 1) - *(s2 + i - 1));
	return (*(s1 + i) - *(s2 + i));
}

static wchar_t	*ft_wstrnew(size_t size)
{
	wchar_t *str;

	str = ft_memalloc((size + 1) * sizeof(wchar_t));
	if (!str)
		return (NULL);
	else
		ft_memset(str, '\0', size + 1);
	return (str);
}

static size_t	ft_wstrlen(const wchar_t *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static wchar_t	*extract_wstring(t_m *m)
{
	wchar_t *arg;

	m->place->precision = m->place->precision == -1 ? 0 : m->place->precision;
	arg = va_arg(m->ap, wchar_t*);
	arg = arg ? arg : L"(null)";
	return (arg);
}

int				wstr(t_m *m, char buf[MAX])
{
	wchar_t	*arg;
	int		l;
	int		i;
	int		p;
	int		w;

	arg = extract_wstring(m);
	if (!ft_wstrncmp(arg, L"", ((l = ft_wstrlen(arg)) ? l : 1)))
	{
		arg = m->place->precision ? ft_wstrnew(m->place->precision) : arg;
		m->place->precision = 0;
	}
	p = !m->place->precision ? ft_wstrlen(arg) : m->place->precision;
	w = m->place->width - p;
	i = -1;
	if (!(m->place->flags & MINUS))
		while (w-- > 0)
			buf[m->pos_b++] = (char)L' ';
	while (arg[++i] && i < p)
		buf[m->pos_b++] = (char)arg[i];
	if (m->place->flags & MINUS)
		while (w-- > 0)
			buf[m->pos_b++] = (char)L' ';
	return (0);
}
