/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_methods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:49:30 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/17 10:52:50 by pstringe         ###   ########.fr       */
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
		server->request.size = read(server->c_sock, &(server->request.text), SOCK_BUF_SIZE);
		ft_putendl(server->request.text);
		if (!server->dispatch(server))
			server->respond(server, "command not recognized", 22);
	}
	close(server->c_sock);
}

/*
** server dispatch
*/

int		dispatch(t_server *server)
{
	int 	i;
	char 	client_input[SOCK_BUF_SIZE];

	ft_bzero(client_input, SOCK_BUF_SIZE);
	ft_memcpy(client_input, server->request.text, server->request.size);  
	i = -1;
	while (server->cmds[++i].name)
	{
		if (!ft_strncmp(client_input, server->cmds[i].name, ft_strlen(client_input)))
		{
			server->request.command.name = server->cmds[i].name;
			server->request.command.action = server->cmds[i].action;
			server->cmds[i].action(server);
			if (i)
				server->history.update(server);
			return (1);
		}
	}
	ft_bzero(&(server->request.command.name), sizeof(t_command));
	server->history.update(server);
	return (0);
}
