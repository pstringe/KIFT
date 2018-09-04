/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 18:49:16 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/21 14:47:53 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *sm, size_t len)
{
	size_t i;

	if (*sm == '\0')
	{
		return ((char *)big);
	}
	i = ft_strlen(sm);
	while (*big != '\0' && len >= i)
	{
		if (ft_strncmp(big, sm, i) == 0)
		{
			return ((char *)big);
		}
		big++;
		len--;
	}
	return (NULL);
}
