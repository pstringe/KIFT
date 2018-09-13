/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 13:57:55 by pstringe          #+#    #+#             */
/*   Updated: 2018/08/02 15:27:21 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_exp(int base, int power)
{
	int res;

	res = 1;
	if (power == 0)
		return (res);
	while (power--)
		res *= base;
	return (res);
}
