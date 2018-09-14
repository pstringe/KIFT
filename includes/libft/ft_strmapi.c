/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 15:36:36 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/20 14:12:26 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	if (s)
	{
		str = ft_strnew(ft_strlen(s));
		if (!str)
		{
			return (NULL);
		}
		i = 0;
		while (*(s + i))
		{
			*(str + i) = (*f)(i, *(s + i));
			i++;
		}
		*(str + i) = '\0';
		return (str);
	}
	return (NULL);
}
