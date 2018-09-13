/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:28:13 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/20 10:13:01 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	cc;
	char	*match;

	match = 0;
	cc = c;
	while (*s || *s == '\0')
	{
		if (*s == cc)
		{
			match = (char *)s;
		}
		if (*s == '\0')
		{
			if (match == 0)
			{
				return (NULL);
			}
			else
			{
				return (match);
			}
		}
		s++;
	}
	return (match);
}
