/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 12:31:53 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/11 12:39:13 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int 	ft_dprintf(int fd, const char *format, ... )
{
	va_list ap;

	va_start(ap, format);
	return (ft_vdprintf(fd, format, ap));
}
