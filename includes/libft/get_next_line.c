/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:13:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/04/16 09:29:12 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft(char **arr, char **line)
{
	char *n;
	char *tmp;

	if ((*arr)[0] == '\0')
		return (0);
	tmp = ft_strdup(*arr);
	ft_memdel((void**)arr);
	if ((n = ft_strchr(tmp, '\n')))
	{
		*n = '\0';
		*line = ft_strdup(tmp);
		*arr = ft_strdup(n + 1);
		ft_memdel((void**)&tmp);
	}
	else
	{
		*line = tmp;
		ft_memdel((void**)&arr);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char *arr[FD_LIMIT];
	char		buf[BUFF_SIZE + 1];
	int			bytes;
	char		*tmp;

	if (fd < 0 || fd > FD_LIMIT || !line || (read(fd, buf, 0) < 0))
		return (-1);
	if (!arr[fd])
		arr[fd] = ft_strnew(0);
	while (!ft_strchr(arr[fd], '\n'))
	{
		bytes = read(fd, buf, BUFF_SIZE);
		buf[bytes] = '\0';
		if (bytes == 0)
			break ;
		tmp = ft_strjoin(arr[fd], buf);
		ft_memdel((void**)&arr[fd]);
		arr[fd] = ft_strdup(tmp);
		ft_memdel((void**)&tmp);
	}
	return (ft(&arr[fd], line));
}
