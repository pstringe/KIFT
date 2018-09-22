/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 19:11:53 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/22 11:11:17 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int i;
	int number;
	int is_negetive;

	i = 0;
	number = 0;
	is_negetive = 0;
	while (ft_is_whitespace(str[i]))
		i++;
	if (str[i] == '-')
		is_negetive = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10;
		number = number + str[i] - '0';
		i++;
	}
	if (is_negetive)
	{
		return (-number);
	}
	return (number);
}
