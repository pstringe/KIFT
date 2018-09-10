/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 06:49:20 by pstringe          #+#    #+#             */
/*   Updated: 2018/07/23 11:51:55 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	handels conversion for number types
*/

int		dig(t_m *m, char buf[MAX])
{
	int		ret;
	char	*tmp;
	t_num	n;

	get_base(m, &n);
	m->place->flags |= (m->place->type == 2 ? HASH : 0);
	get_num(m, &n);
	if (m->place->precision == 0 &&
			!ft_strncmp(n.b_conv, "0", 1) &&
			!(n.base == 8 && (m->place->flags & HASH)))
	{
		tmp = ft_strnew(m->place->width);
		ft_memset(tmp, ' ', m->place->width);
		ret = replace(m, buf, tmp);
		ft_memdel((void**)&tmp);
		return (ret);
	}
	num_prcs(&n, m->place->precision);
	num_wdth(m, &n, m->place->width, m->place->flags);
	flags(m, &n);
	return (replace(m, buf, n.b_conv));
}
