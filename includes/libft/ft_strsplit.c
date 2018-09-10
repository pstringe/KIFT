/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 16:11:48 by pstringe          #+#    #+#             */
/*   Updated: 2017/12/22 10:26:30 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_count_words(const char *str, char delimiter)
{
	int is_not_delimeter;
	int number_of_words;

	is_not_delimeter = 0;
	number_of_words = 0;
	if (!str || !delimiter)
	{
		return (0);
	}
	while (*str)
	{
		if (*str == delimiter && is_not_delimeter)
		{
			is_not_delimeter = 0;
		}
		if (*str != delimiter && !is_not_delimeter)
		{
			is_not_delimeter = 1;
			number_of_words++;
		}
		str++;
	}
	return (number_of_words);
}

static int	ft_word_len(const char *str, char delimiter)
{
	int length_of_word;

	length_of_word = 0;
	while (*str != delimiter && *str != '\0')
	{
		length_of_word++;
		str++;
	}
	return (length_of_word);
}

char		**ft_strsplit(char const *str, char delimiter)
{
	int		i;
	int		number_of_words;
	char	**splitstr;

	i = 0;
	number_of_words = ft_count_words(str, delimiter);
	splitstr = (char **)malloc(sizeof(*splitstr) * (number_of_words + 1));
	if (splitstr == NULL)
	{
		return (NULL);
	}
	while (number_of_words--)
	{
		while (*str == delimiter && *str != '\0')
		{
			str++;
		}
		splitstr[i] = ft_strsub(str, 0, ft_word_len(str, delimiter));
		str = str + ft_word_len((const char *)str, delimiter);
		i++;
	}
	splitstr[i] = NULL;
	return (splitstr);
}
