/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 10:04:42 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/22 11:16:41 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*strnew(int is_negitive, size_t size)
{
	char *str;

	if ((str = (char *)malloc(sizeof(char) * size + 1)))
	{
		if (is_negitive)
		{
			str[0] = '-';
		}
		str[size] = '\0';
	}
	return (str);
}

char			*ft_itoa(int n)
{
	char			*str;
	int				is_negitive;
	int				length_of_number;
	int				i;
	unsigned int	j;

	is_negitive = 0;
	if (n < 0)
	{
		is_negitive = 1;
	}
	length_of_number = ft_nbrlen(n) + is_negitive;
	j = ft_absval(n);
	if ((str = strnew(is_negitive, (size_t)length_of_number)))
	{
		i = length_of_number - 1;
		while (i >= is_negitive)
		{
			str[i] = (char)(j % 10) + 48;
			j = j / 10;
			i--;
		}
	}
	return (str);
}
