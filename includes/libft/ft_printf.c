/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 15:20:51 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/11 11:08:16 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	 ft_printf(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	return (ft_vdprintf(1, format, ap));
}
