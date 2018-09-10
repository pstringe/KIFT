/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 14:58:33 by pstringe          #+#    #+#             */
/*   Updated: 2018/08/14 13:34:12 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*str;
	
	if (!s1)
		return (ft_strdup(s2));
	if ((str = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)) && s1 && s2)
	{
		i = 0;
		while (*s1)
		{
			*(str + i) = *s1;
			s1++;
			i++;
		}
		while (*s2)
		{
			*(str + i) = *s2;
			s2++;
			i++;
		}
		*(str + i) = '\0';
		return (str);
	}
	return (NULL);
}
