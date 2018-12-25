/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_methods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:49:30 by pstringe          #+#    #+#             */
/*   Updated: 2018/12/24 17:11:34 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
**	This function is called to establish a connection with the client machine
*/

int		establish_connection(t_server *server, int argc)
{
	if (argc != 2)
	{
		perror("please specify port to listen on");
		return (-1);
	}

	//create master socket
	if (!(server->m_sock = socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("failed to get socket descriptor");
		return (-1);
	}

	//set master socket to allow multiple connections
	if (setsckopt(server->m_sock, SOL_SOCKET, SO_REUSEADDR, \
				(char *)&(server->opt), sizeof(server->opt)) < 0 )
	{
		perror("setsocketopt");
		return(-1);
	}

	server->addr.sin_family = AF_INET;
	server->addr.sin_addr.s_addr = INADDR_ANY;
	server->addr.sin_port = htons(server->port);
	server->addr_len = sizeof(server->addr);
	
	//bind port to master socket
	if (bind(server->m_sock, (struct sockaddr*)&(server->addr), 
				(socklen_t)sizeof(server->addr)) < 0)
	{
		perror("faild to bind port to address");
		return (-1);
	}

	//maximum 5 pending connections for master socket
	if (listen(server->m_sock, 5) == -1)
		perror("server is not listening");
	else
		server->listening = 1;
	return (0);
}

/*
** A function to for writing to  the response object and sending it off
*/

void	respond(t_server *server, char *msg, size_t size)
{
	ft_bzero(server->response.txt, SOCK_BUF_SIZE);
	ft_memcpy(server->response.txt, msg, size);
	server->response.size = size;
	write(server->c_sock, server->response.txt, server->response.size);
}

/*
**	this is the called for the server to listen continuosly on the read socket and
**	having registered a valid command, exit.
*/

void	listening(t_server *server)
{
	server->c_sock = accept(server->s_sock, (struct sockaddr*)&(server->addr), (socklen_t*)&(server->addr_len));
	while (server->listening)
	{
		if (server->c_sock < 0)
			perror("did not accept");
		ft_bzero(server->request.text, SOCK_BUF_SIZE);
		if ((server->request.size = read(server->c_sock, &(server->request.text), SOCK_BUF_SIZE)))
		{
			ft_putendl(server->request.text);
			if (!server->dispatch(server))
				server->respond(server, "command not recognized", 22);
		}
	}
	close(server->c_sock);
}

/*
** server dispatch
*/

int		dispatch(t_server *server)
{
	int 	i;

	i = -1;
	while (server->cmds[++i].name)
	{
		if (!ft_strncmp(server->request.text, server->cmds[i].name, SOCK_BUF_SIZE))
		{
			server->request.command.name = server->cmds[i].name;
			server->request.command.action = server->cmds[i].action;
			server->cmds[i].action(server);
			if (i)
				server->history.update(server);
			return (1);
		}
	}
	server->request.command.name = NULL;
	server->history.update(server);
	return (0);
}
