/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:26:55 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/20 10:28:21 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char			*s1;
	const char		*s2;
	unsigned char	cc;

	s1 = (char *)dst;
	s2 = (const char *)src;
	cc = (unsigned char)c;
	while (n-- != 0)
	{
		if ((unsigned char)*s2 != cc)
		{
			ft_memcpy(s1, s2, 1);
			s1++;
			s2++;
		}
		else
		{
			ft_memcpy(s1, s2, 1);
			s1++;
			return (s1);
		}
	}
	return (NULL);
}
