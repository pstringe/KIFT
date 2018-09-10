/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 15:18:34 by pstringe          #+#    #+#             */
/*   Updated: 2018/07/23 13:49:33 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	calculates the space left to copy the prefix
*/

static int	space_left(t_num *n, t_f f)
{
	char	w;
	int		s;
	int		i;

	s = n->base == 16 ? 2 : 1;
	w = f.z ? '0' : ' ';
	i = -1;
	while (n->b_conv[++i] == w)
	{
	}
	return (i >= s ? i : 0);
}

/*
**	handles hash flag for hexadecimal conversions
*/

void		hex_hash(t_m *m, t_num *n, t_f flags, int ol)
{
	char	tmp[100];
	int		pos;

	if ((pos = space_left(n, flags)))
		ft_memcpy(n->b_conv + (*n->b_conv == ' ' ? pos - 2 : 0),
				(m->place->type == 11 ? "0X" : "0x"), 2);
	else
	{
		ft_bzero(tmp, 100);
		ft_memcpy(tmp, (m->place->type == 11 ? "0X" : "0x"), 2);
		ft_strlcat(tmp, n->b_conv, 100);
		ft_memcpy(n->b_conv, tmp, ((flags.m && ol <= m->place->width) ?
					m->place->width : ft_strlen(tmp)));
	}
}

/*
** handles hash flag for octal conversions
*/

void		octal_hash(t_num *n, t_f flags)
{
	char	tmp[100];
	int		pos;

	if ((pos = space_left(n, flags)))
		n->b_conv[pos - 1] = '0';
	else
	{
		ft_bzero(tmp, 100);
		ft_memcpy(tmp, "0", 1);
		ft_strlcat(tmp, n->b_conv, 100);
		ft_memcpy(n->b_conv, tmp, ft_strlen(tmp));
	}
}

void		plus(t_num *n, int flags)
{
	if (*(n->b_conv) == '0')
		n->b_conv[0] = get_signchar(n, flags);
}

/*
**	handles any flags that weren't handled in precision and width
*/

void		flags(t_m *m, t_num *n)
{
	int		ol;
	t_f		flags;

	init_f(&flags, m);
	ol = ft_strlen(n->b_conv);
	if ((flags.h && (ft_strncmp("0", n->b_conv, ft_strlen(n->b_conv)))) ||
				(flags.h && m->place->type == 2))
	{
		if (n->base == 16)
			hex_hash(m, n, flags, ol);
		else if (n->base == 8 && n->b_conv[0] != '0')
		{
			octal_hash(n, flags);
		}
	}
	if (flags.p)
		plus(n, m->place->flags);
}
