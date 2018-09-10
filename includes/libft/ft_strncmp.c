/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 19:36:40 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/20 13:37:46 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (*(s1 + i) == *(s2 + i) && *(s1 + i) && i < n)
	{
		i++;
	}
	if (i == n)
	{
		return ((unsigned char)*(s1 + i - 1) - (unsigned char)*(s2 + i - 1));
	}
	return ((unsigned char)*(s1 + i) - (unsigned char)*(s2 + i));
}
