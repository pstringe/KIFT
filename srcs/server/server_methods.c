/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiserver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:18:30 by pstringe          #+#    #+#             */
/*   Updated: 2019/02/23 01:18:31 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
**	a function to make system calls from a seperate process
*/

void	call_cmd(char *cmd)
{
	if (fork() == 0)
		return ;
	else
		system(cmd);
	exit(0);
}

/*
** initialize client sockets to 0
*/

void	init_client_socks(t_server *s)
{
	int i;

	i = -1;
	while (++i < MAX_CLIENTS)
		s->c_sock[i] = 0;
}

/*
**	initialize master socket
*/

void	init_master(t_server *s)
{
	if ((s->m_sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		ft_putendl("error creating master socket");
		return ;
	}
	if (setsockopt(s->m_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&(s->opt), sizeof(s->opt)) < 0)
	{
		ft_putendl("error setsockopt");
		return ;
	}
	s->addr.sin_family = AF_INET;
	s->addr.sin_addr.s_addr = INADDR_ANY;
	s->addr.sin_port = htons(s->port);
	if (bind(s->m_sock, (struct sockaddr *)&s->addr, sizeof(s->addr)) < 0)
	{
		ft_printf("error binding, error code: %d\n", errno);
		exit(1);
	}
	ft_printf("master socket: %d, initialized on port: %d\n", s->m_sock, s->port);
}

/*
**	Here, we add sockets to the fd structure 
*/

void	add_child_sockets(t_server *s)
{
	int i;
	
	i = -1;
	while (++i < MAX_CLIENTS)
	{
		s->sd = s->c_sock[i];
		if (s->sd > 0)
			FD_SET(s->sd, &(s->fds));
		if (s->sd > s->max_sd)
			s->max_sd = s->sd;
	} 
}

/*
**	We call this function to add a new socket to our fd set when we get a new
**	incoming client connection.
*/

void	add_new_users(t_server *s)
{
	int i;
	
	i = -1;
	while (++i < MAX_CLIENTS)
	{
		if (s->c_sock[i] == 0)
		{
			s->c_sock[i] = s->n_sock;
			s->l_sock = s->n_sock;
			new_user(s);
			ft_printf("user, %s added on as client, %d socket %d\n", s->users->tail->content, i, s->n_sock);
			s->respond(s, "User Added", 11);
			break ;
		}
	}
}

/*
**	Here, we accept an incoming connection on the master socket and return a
**	a new socket to manage connections to this particular client.
*/

void	handle_new_connections(t_server *s)
{
	int	l;

	l = ft_strlen(s->msg);
	if(FD_ISSET(s->m_sock, &(s->fds)))
	{
		if ((s->n_sock = accept(s->m_sock, (struct sockaddr *)&(s->addr), (socklen_t *)&(s->addr))) < 0)
			return ;
		if (fcntl(s->n_sock, F_SETFL, O_NONBLOCK) < 0 )
			return ;
		ft_putendl("New Connection");
		/*
		if (write(s->n_sock, s->msg, l) != l)
			return ;
		*/
		ft_putendl("response sent");
		add_new_users(s);
	}
}

/*
** A function to for writing to  the response object and sending it off
*/

void	respond(t_server *server, char *msg, int size)
{
	if (size == -1)
		size = ft_strlen(msg);
	ft_bzero(server->response.txt, SOCK_BUF_SIZE);
	ft_memcpy(server->response.txt, msg, size);
	server->response.size = size;
	ft_printf("writing response of size: %d bytes\nresponse sample: %.30s ...\n", size, server->response.txt);
	write(server->l_sock, server->response.txt, server->response.size);
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

/*
**	A function to prompt the client for a certain response Eventually, 
** I may pass a function pointer to handel the request, but this will do for now
*/

t_request	prompt_request(t_server *s, int socket, char *prompt)
{
	if (prompt)
		respond(s, prompt, ft_strlen(prompt));

	ft_bzero(s->request.text, BUF_SIZE);

	/*Here, we need the read to block*/
	while ((s->request.size = read(socket, &(s->request.text), BUF_SIZE)) < 0);
	return (s->request);
}

/*
** Here we check for socket closure on the client side, if not, we perform an 
** operation based on the input ( dispatch() )
*/

void	handle_existing_connections(t_server *s)
{
	int	i;

	i = -1;
	while (++i < s->max_sd && s->c_sock[i])
	{
		s->sd = s->c_sock[i];
		if (!prompt_request(s, s->sd, NULL).size)
		{
			getpeername(s->sd, (struct sockaddr*)&(s->addr), (socklen_t*)&(s->addrlen));
			ft_printf("Host disconnected, ip %s, port %d\n", inet_ntoa(s->addr.sin_addr), ntohs(s->addr.sin_port));
			close(s->sd);
			s->c_sock[i] = 0; 
		}
		else if (s->sd < 0)
			perror("socket descriptor: sd, returns less than 0\n");
		else
		{
			s->l_sock = s->sd;
			if (s->request.size)
			{
				ft_putendl(s->request.text);
				if (!s->dispatch(s) && s->request.size > 0)
					s->respond(s, "command not recognized", 22);
			}
		}
	}
}


/*
**	listen for incoming connections on master socket, determine whether they
**	come from new or existing clients, and act accordingly
*/

void	listening(t_server *s)
{
	if (listen(s->m_sock, 3) < 0)
		return ;
	s->addrlen = sizeof(s->addr);
	ft_putendl("waiting for connections");
	while (TRUE)
	{
		FD_ZERO(&(s->fds));
		FD_SET(s->m_sock, &(s->fds));
		s->max_sd = s->m_sock;
		add_child_sockets(s);
		s->activity = select( s->max_sd + 1, &(s->fds), NULL, NULL, NULL);
		if (s->activity < 0 && errno != EINTR)
			ft_printf("select error\n");
		handle_new_connections(s);
		handle_existing_connections(s);
	}
	return ;
}
