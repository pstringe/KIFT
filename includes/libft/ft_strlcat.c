/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:21:38 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/22 09:32:19 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	length_of_src;
	size_t	length_of_dst;
	size_t	space_left_in_buffer;

	length_of_dst = ft_strlen(dst);
	length_of_src = ft_strlen(src);
	space_left_in_buffer = size - length_of_dst - 1;
	if (length_of_dst < size)
	{
		ft_memcpy((dst + length_of_dst), src, space_left_in_buffer);
		*(dst + (size - 1)) = '\0';
		return (length_of_dst + length_of_src);
	}
	return (size + length_of_src);
}
