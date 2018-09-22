/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:50:58 by pstringe          #+#    #+#             */
/*   Updated: 2018/07/23 13:13:20 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	a function to determine whether there will be an extra char prepended to
**	the string
*/

int		get_echar(t_num *n, t_w *spec, int flags)
{
	if (!spec->z && (n->sign < 0 || flags & SPACE || flags & PLUS))
		return (1);
	else if (n->sign < 0)
		return (1);
	return (0);
}

/*
**	determines what charater should be prepended to the number string
*/

int		get_signchar(t_num *n, int flags)
{
	if (n->sign < 0)
		return ('-');
	if (flags & SPACE)
		return (' ');
	if (flags & PLUS)
		return ('+');
	return (0);
}
