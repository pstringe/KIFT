/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:41:06 by pstringe          #+#    #+#             */
/*   Updated: 2018/07/23 11:13:00 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	initialized a struct to easily deal with flags
*/

void	init_f(t_f *flags, t_m *m)
{
	int f;

	f = m->place->flags;
	flags->m = f & MINUS;
	flags->p = f & PLUS;
	flags->s = f & SPACE;
	flags->z = f & ZERO;
	flags->h = f & HASH;
}

void	init_funcs(int (*con[NO_OF_TYPES])(t_m*, char buf[MAX]))
{
	con[0] = &str;
	con[1] = &wstr;
	con[2] = &dig;
	con[3] = &dig;
	con[4] = &dig;
	con[5] = &dig;
	con[6] = &dig;
	con[7] = &dig;
	con[8] = &dig;
	con[9] = &dig;
	con[10] = &dig;
	con[11] = &dig;
	con[12] = &chr;
	con[13] = &chr;
	con[14] = &not;
}

void	init_lens(char *lens[NO_OF_LENS])
{
	lens[0] = "hh";
	lens[1] = "ll";
	lens[2] = "l";
	lens[3] = "h";
	lens[4] = "j";
	lens[5] = "z";
}

void	init(t_m *m, const char *format, char buf[MAX])
{
	m->pos_b = 0;
	m->pos_f = 0;
	m->format = format;
	ft_bzero(buf, MAX);
	m->place = NULL;
}
