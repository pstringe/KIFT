/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 18:00:31 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/20 13:34:27 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *unsigned_1;
	const unsigned char *unsigned_2;

	unsigned_1 = (const unsigned char *)s1;
	unsigned_2 = (const unsigned char *)s2;
	while (n-- != 0)
	{
		if (*unsigned_1 != *unsigned_2)
		{
			if (*unsigned_1 < *unsigned_2)
			{
				return ((*unsigned_2 - *unsigned_1) * -1);
			}
			else
			{
				return (*unsigned_1 - *unsigned_2);
			}
		}
		unsigned_1++;
		unsigned_2++;
	}
	return (0);
}
