/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hydra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 17:52:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/03/03 20:19:28 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define BUFF_SIZE 256

int		main(int argc, char **argv)
{
	int					listening;
	int					port;
	int 				ret;
	int					s_sock;
	int					c_sock;
	char 				*msg;
	char 				buf[BUFF_SIZE];
	struct sockaddr_in	addr;
	socklen_t			addr_len;

	if (argc != 2)
	{
		perror("please specify port to listen on");
		return (-1);
	}
	if (!(s_sock = socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("failed to get socket descriptor");
		return (-1);
	}
	port = ft_atoi(argv[1]);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	addr_len = sizeof(addr);
	if (bind(s_sock, (struct sockaddr*)&addr, (socklen_t)sizeof(addr)) < 0)
	{
		perror("faild to bind port to address");
		return (-1);
	}
	if (listen(s_sock, 5) == -1)
	{
		perror("server is not listening");
	}
	listening = 1;
	while (listening)
	{
		c_sock = accept(s_sock, (struct sockaddr*)&addr, (socklen_t*)&addr_len);
		if (c_sock < 0)
		{
			perror("did not accept");
		}
		ft_bzero(buf, BUFF_SIZE);
		ret = read(c_sock, &buf, BUFF_SIZE);
		ft_putendl(buf);
		if (!ft_strncmp(buf, "ping", ft_strlen(buf)))
			msg = "pong pong";
		else if (!ft_strncmp(buf, "quit", ft_strlen(buf)))
		{
			listening = 0;
			msg = "quit";
		}
		else
		{
			msg = "command not recongnized";
		}
		write(c_sock, msg, ft_strlen(msg));
		close(c_sock);
	}
	return(0);
}
