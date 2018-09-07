/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 13:54:16 by pstringe          #+#    #+#             */
/*   Updated: 2018/07/23 13:08:14 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	skip_whitespace(t_m *m)
{
	while (ft_is_whitespace(m->format[m->pos_f]))
		m->pos_f++;
}

/*
** writes resulting conversion to bufffer
*/

int		replace(t_m *m, char buf[MAX], char *conv)
{
	int	i;

	i = -1;
	while (conv[++i] && m->pos_b + i < MAX)
		buf[m->pos_b + i] = conv[i];
	m->pos_b += i;
	return (0);
}

/*
**	checks that a character is a flag
*/

int		is_flag(char c)
{
	int		i;
	char	*flags;

	flags = FLAGS;
	i = -1;
	while (flags[++i])
		if (c == flags[i])
			return (i + 1);
	return (0);
}

/*
**	prints the result
*/

void	put(t_m *m, char buf[MAX])
{
	write(1, buf, m->pos_b);
}

/*
**	cleanup
*/

void	dstry(t_m *m)
{
	if (m->place)
		ft_memdel((void**)&m->place);
	va_end(m->ap);
	ft_memdel((void**)&m);
}
