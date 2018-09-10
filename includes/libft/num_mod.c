/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 16:06:17 by pstringe          #+#    #+#             */
/*   Updated: 2018/07/23 12:57:45 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	edits number string to accomodate precision specification
*/

void	num_prcs(t_num *n, int pr)
{
	int		l;
	char	*tmp;
	char	*p;

	pr = pr == -1 ? 0 : pr;
	l = ft_strlen(n->b_conv);
	p = l < pr ? ft_strnew(pr - l) : NULL;
	if (p)
	{
		tmp = ft_strdup(n->b_conv);
		ft_memset(p, '0', pr - l);
		ft_memcpy(n->b_conv, p, pr - l);
		n->p_len = pr - l;
		ft_memdel((void**)&p);
		ft_memcpy(n->b_conv + pr - l, tmp, l);
		ft_memdel((void**)&tmp);
	}
	n->idx += pr - l;
}

/*
**	appplies padding at the begining of the string while prepending the
**	appropriate extra.
**	characters as determines by flags
*/

void	prepend(t_num *n, t_w *spec, int wd, int flags)
{
	char	*tmp;

	tmp = ft_strdup(n->b_conv);
	ft_memcpy(n->b_conv, spec->w, wd - spec->l);
	if ((spec->e_char = get_echar(n, spec, flags)))
	{
		n->b_conv[wd - spec->l - 1] = get_signchar(n, flags);
		n->neg = 1;
	}
	ft_memdel((void**)&spec->w);
	ft_memcpy(n->b_conv + wd - spec->l, tmp, spec->l);
	n->w_len = spec->l;
	ft_memdel((void**)&tmp);
}

/*
**	applies padding at the end of the string while prepending the
**	appropriate extra.
**	characters as determines by flags
*/

void	append(t_num *n, t_w *spec, int wd, int flags)
{
	char	*tmp;

	tmp = ft_strdup(n->b_conv);
	if ((spec->e_char = (!spec->z &&
					(n->sign < 0 || flags & SPACE || flags & PLUS))))
	{
		n->b_conv[0] = get_signchar(n, flags);
		ft_memcpy(n->b_conv + 1, tmp, spec->l);
	}
	ft_memcpy(n->b_conv + spec->l + (spec->e_char ? 1 : 0),
			spec->w, wd - spec->l - (spec->e_char ? 1 : 0));
	n->w_len = wd + (spec->e_char ? -2 : -1);
	ft_memdel((void**)&spec->w);
	ft_memdel((void**)&tmp);
}

/*
**	evaluates width_char
*/

char	width_char(t_m *m, t_w spec, int wd)
{
	int	p;

	p = m->place->precision;
	if (spec.z && (p != -1 && p < wd))
		return (' ');
	if (spec.z)
		return ('0');
	else
		return (' ');
}

/*
**	edits string to accomadte sign and any other extra characters
**	needed for flags while complying with width specification
*/

void	num_wdth(t_m *m, t_num *n, int wd, int flags)
{
	t_w		spec;
	char	*tmp;
	char	s;

	spec.l = ft_strlen(n->b_conv);
	spec.z = ((flags & ZERO) && !(flags & MINUS)) &&
		ft_strncmp("0", n->b_conv, spec.l);
	spec.w = spec.l < wd ? ft_strnew(wd - spec.l) : NULL;
	spec.e_char = 0;
	if (spec.w)
		ft_memset(spec.w, width_char(m, spec, wd), wd - spec.l);
	if (spec.w && !(flags & MINUS))
		prepend(n, &spec, wd, flags);
	else if (spec.w && (flags & MINUS))
		append(n, &spec, wd, flags);
	else if ((s = get_signchar(n, flags)))
	{
		tmp = ft_strdup(n->b_conv);
		n->b_conv[0] = get_signchar(n, flags);
		ft_memcpy(n->b_conv + 1, tmp, ft_strlen(n->b_conv));
		ft_memdel((void**)&tmp);
	}
	n->idx += wd - spec.l + (spec.e_char ? -1 : 0);
}
