/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 06:28:44 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/30 13:39:22 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoab(uintmax_t n, int base)
{
	int		i;
	char	*str;

	str = ft_strnew(12 + 1);
	i = 12;
	while (n)
	{
		str[--i] = (n % base > 9) ? n % base - 10 + 'a' : n % base + '0';
		n /= base;
	}
	return (str);
}

int		poi(t_m *m, char buf[MAX])
{
	uintmax_t	arg;
	int			l;
	char		*str;

	arg = va_arg((m->ap), uintmax_t);
	str = ft_strjoin("0x", ft_itoab(arg, 16));
	ft_memcpy(buf + m->pos_b, str, (l = ft_strlen(str)));
	m->pos_b += l;
	ft_memdel((void**)&str);
	return (l);
}
