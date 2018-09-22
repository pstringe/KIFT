/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 18:22:37 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/20 10:34:02 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char *ss = (const char *)s;

	while (n)
	{
		if (*ss == (char)c)
		{
			return ((void *)ss);
		}
		ss++;
		n--;
	}
	return (NULL);
}
