/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:57:08 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/22 11:07:57 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_whitespace_lite(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
	{
		return (1);
	}
	return (0);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	int		end;
	int		start;

	if (s == NULL)
	{
		return (NULL);
	}
	start = 0;
	end = ft_strlen(s) - 1;
	while (ft_is_whitespace_lite(*(s + start)))
	{
		start++;
	}
	while (ft_is_whitespace_lite(*(s + end)) && end > 0)
	{
		end--;
	}
	if (*(s + start) == '\0')
	{
		return (ft_strnew(0));
	}
	str = ft_strsub(s, start, end - start + 1);
	return (str);
}
