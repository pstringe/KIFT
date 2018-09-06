/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_methods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:49:30 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/05 20:06:23 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
**	This function is called to establish a connection with the client machine
*/

int		establish_connection(t_server *server, int argc, char **argv)
{
	if (argc != 2)
	{
		perror("please specify port to listen on");
		return (-1);
	}
	if (!(server->s_sock = socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("failed to get socket descriptor");
		return (-1);
	}
	server->port = ft_atoi(argv[1]);
	server->addr.sin_family = AF_INET;
	server->addr.sin_addr.s_addr = INADDR_ANY;
	server->addr.sin_port = htons(server->port);
	server->addr_len = sizeof(server->addr);
	if (bind(server->s_sock, (struct sockaddr*)&(server->addr), 
				(socklen_t)sizeof(server->addr)) < 0)
	{
		perror("faild to bind port to address");
		return (-1);
	}
	if (listen(server->s_sock, 5) == -1)
		perror("server is not listening");
	else
		server->listening = 1;
	return (0);
}

/*
**	this is the called for the server to listen continuosly on the read socket and
**	having registered a valid command, exit.
*/

void	listening(t_server *server)
{
	char 		buf[SOCK_BUF_SIZE];
	char 		*msg;
	size_t		ret;
	
	while (server->listening)
	{
		server->c_sock = accept(server->s_sock, (struct sockaddr*)&(server->addr), (socklen_t*)&(server->addr_len));
		if (server->c_sock < 0)
			perror("did not accept");
		ft_bzero(buf, SOCK_BUF_SIZE);
		ret = read(server->c_sock, &buf, SOCK_BUF_SIZE);
		ft_putendl(buf);
		if (!ft_strncmp(buf, "ping", ft_strlen(buf)))
			msg = "pong pong";
		else if (!ft_strncmp(buf, "quit", ft_strlen(buf)))
		{
			server->listening = 0;
			msg = "quit";
		}
		else
			msg = "command not recongnized";
		write(server->c_sock, msg, ft_strlen(msg));
		close(server->c_sock);
	}
}

void	test_method(t_server *server)
{
	ft_bzero(server->response.)
}

/*
** server dispatch
*/

void	dispatch(t_server *server, char *cmd)
{
	int i;
	
	s_commands cmds = {
		{"test", test_method}
		{NULL}
	};

	i = -1;
	while ((++i))
}
