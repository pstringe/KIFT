/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 17:52:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/05 19:02:38 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		main(int argc, char **argv)
{
	size_t		ret;
	t_server	server;
	char 		*msg;
	char 		buf[SOCK_BUF_SIZE];

	if (argc != 2)
	{
		perror("please specify port to listen on");
		return (-1);
	}
	if (!(server.s_sock = socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("failed to get socket descriptor");
		return (-1);
	}
	server.port = ft_atoi(argv[1]);
	server.addr.sin_family = AF_INET;
	server.addr.sin_addr.s_addr = INADDR_ANY;
	server.addr.sin_port = htons(server.port);
	server.addr_len = sizeof(server.addr);
	if (bind(server.s_sock, (struct sockaddr*)&(server.addr), 
				(socklen_t)sizeof(server.addr)) < 0)
	{
		perror("faild to bind port to address");
		return (-1);
	}
	if (listen(server.s_sock, 5) == -1)
	{
		perror("server is not listening");
	}
	server.listening = 1;
	while (server.listening)
	{
		server.c_sock = accept(server.s_sock, (struct sockaddr*)&(server.addr), (socklen_t*)&(server.addr_len));
		if (server.c_sock < 0)
		{
			perror("did not accept");
		}
		ft_bzero(buf, BUFF_SIZE);
		ret = read(server.c_sock, &buf, BUFF_SIZE);
		ft_putendl(buf);
		if (!ft_strncmp(buf, "ping", ft_strlen(buf)))
			msg = "pong pong";
		else if (!ft_strncmp(buf, "quit", ft_strlen(buf)))
		{
			server.listening = 0;
			msg = "quit";
		}
		else
		{
			msg = "command not recongnized";
		}
		write(server.c_sock, msg, ft_strlen(msg));
		close(server.c_sock);
	}
	return(0);
}
