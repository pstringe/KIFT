/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:05:08 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/11 11:16:30 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_m		*m;
	size_t	size;
	char	buf[MAX];

	m = (t_m*)ft_memalloc(sizeof(t_m));
	ft_memcpy(m->ap,  ap, sizeof(va_list));
	init(m, format, buf);
	while (cpy(m, buf))
		if (get_placeholder(m))
			convert(m, buf);
	put(fd, m, buf);
	size = m->pos_b;
	dstry(m);
	return (size);
}
