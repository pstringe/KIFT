/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 17:41:43 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/20 13:55:19 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char *bb;
	unsigned char cc;

	bb = b;
	cc = c;
	while (n-- != 0)
	{
		*bb++ = cc;
	}
	return (b);
}
