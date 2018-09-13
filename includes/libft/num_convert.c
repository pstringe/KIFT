/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 16:13:03 by pstringe          #+#    #+#             */
/*   Updated: 2018/06/04 16:17:00 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	signed numerical conversion
*/

void	ft_spn(intmax_t nb, t_num *n, t_m *m)
{
	int			c;

	if (nb < 0)
	{
		nb = -nb;
		n->sign = -1;
	}
	if (nb >= (intmax_t)n->base)
	{
		ft_spn(nb / n->base, n, m);
		ft_spn(nb % n->base, n, m);
	}
	else
	{
		c = (m->place->type == 11) ? 'A' : 'a';
		n->b_conv[(n->idx)++] = nb > 9 ? nb - 10 + c : nb + '0';
	}
}

/*
**	unsigned numerical conversion
*/

void	ft_upn(uintmax_t nb, t_num *n, t_m *m)
{
	int			c;

	if (nb >= (uintmax_t)n->base)
	{
		ft_upn(nb / n->base, n, m);
		ft_upn(nb % n->base, n, m);
	}
	else
	{
		c = (m->place->type == 11) ? 'A' : 'a';
		n->b_conv[(n->idx)++] = nb > 9 ? nb - 10 + c : nb + '0';
	}
}
