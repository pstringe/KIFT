/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_methods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:49:30 by pstringe          #+#    #+#             */
/*   Updated: 2018/12/25 23:55:56 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <errno.h>

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
	if (setsockopt(server->m_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&(server->opt), sizeof(server->opt)) < 0 )
	{
		perror("setsocketopt");
		return(-1);
	}

	server->addr.sin_family = AF_INET;
	server->addr.sin_addr.s_addr = INADDR_ANY;
	server->addr.sin_port = htons(server->port);
	server->addr_len = sizeof(server->addr);
	
	//bind port to master socket
	if (bind(server->m_sock, (struct sockaddr*)&(server->addr), (socklen_t)sizeof(server->addr)) < 0)
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
	int	i;
	int	ret;
	int	highest;
	int	n_sock;
	char buf[1025];
	char *message;

	message = "echo server online\n";
	while(1)
	{
		//clear socket set
		FD_ZERO(&(server->readfds));
		
		//add master socket to set
		FD_SET(server->m_sock, &(server->readfds));

		//add child sockets to set
		i = -1;
		while (++i < MAX_CLIENTS)
		{
			//socket descriptor
			server->sd = server->client_sockets[i];
			
			//add to list if valid
			if (server->sd > 0)
				FD_SET(server->sd, &(server->readfds));

			//get highest file descripter
			if (server->sd > highest)
				highest = server->sd;
		}

		//wait for activity on one of the sockets
		server->activity = select(highest + 1, &(server->readfds), NULL, NULL, NULL);
		if (server->activity < 0 && errno != EINTR)
			printf("selcect error");

		//handle incoming connections
		if (FD_ISSET(server->m_sock, &(server->readfds)))
		{
			if ((n_sock = accept(server->m_sock, (struct sockaddr *)&(server->addr), (socklen_t*)&(server->addr_len))) < 0)
			{
				perror("accept");
				return ;
			}
		}
		printf("New Connection\nsocketfd: %d,\nip: %s,\nport: %d\n", n_sock, inet_ntoa(server->addr.sin_addr), ntohs(server->addr.sin_port));
		
		//send new connection message
		if (send(n_sock, message, ft_strlen(message), 0) != (ssize_t)ft_strlen(message))
			perror("send");
		ft_putendl("welcome sent success");
		
		//add socket to array
		i = -1;
		while (++i)
		{
			if (!server->client_sockets[i])
			{
				server->client_sockets[i] = n_sock;
				ft_printf("Adding to list of sockets");
				break;
			}
		}
	}
	
	//handle IO operation
	i = -1;
	while (++i < MAX_CLIENTS)
	{
		server->sd = server->client_sockets[i];
		if (FD_ISSET(server->sd, &(server->readfds)))
		{
			//check if was close and read message
			if ((ret = read(server->sd, buf, 1024)) == 0)
			{
				//get disconnected client details
				getpeername(server->sd, (struct sockaddr*)&server->addr, (socklen_t*)&server->addr_len);
				ft_printf("Host disconnected, ip is: %s, port %d\n", inet_ntoa(server->addr.sin_addr), ntohs(server->addr.sin_port));

				//Close socket and zero it out
				close(server->sd);
				server->client_sockets[i] = 0;
			}
		}

		//Echo the message that came in
		else
		{
			//terminate the buffer
			buf[ret] = '\0';
			send(server->sd, buf, ft_strlen(buf), 0);
		}
	}
	/*
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
	*/

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
