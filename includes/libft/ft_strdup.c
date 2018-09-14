/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 11:55:56 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/20 10:31:53 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dest;

	if (!(dest = (char*)malloc(ft_strlen(str) + 1)))
	{
		return (NULL);
	}
	dest = ft_strcpy(dest, str);
	return (dest);
}
