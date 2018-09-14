/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:35:02 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/20 10:20:56 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *s1, const char *s2, size_t len)
{
	char		*dst;
	const char	*src;

	src = s2;
	dst = s1;
	while (len > 0)
	{
		len--;
		if ((*dst++ = *src++) == '\0')
		{
			ft_memset(dst, '\0', len);
			break ;
		}
	}
	return (s1);
}
