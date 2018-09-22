/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 19:57:59 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/20 13:47:32 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
	{
		return (0);
	}
	i = 0;
	while (*(s1 + i) && *(s2 + i) && *(s1 + i) == *(s2 + i))
	{
		i++;
	}
	if ((unsigned char)*(s1 + i) - (unsigned char)*(s2 + i) == 0)
	{
		return (1);
	}
	return (0);
}
