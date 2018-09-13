/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 14:15:23 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/11 14:37:31 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;

	if ((sub_str = ft_strnew(len)) == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (len--)
	{
		sub_str[i++] = s[start++];
	}
	sub_str[i] = '\0';
	return (sub_str);
}
