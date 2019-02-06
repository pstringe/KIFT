/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiserver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:18:30 by pstringe          #+#    #+#             */
/*   Updated: 2019/02/06 08:47:39 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
** commenting this struct out since I added it's parts to the s_server header
**
typedef struct s_server
{
	int					opt;
	int					m_sock;
	int					addrlen;
	int					n_sock;
	int					c_sock[MAX_CLIENTS];
	int					activity;
	int					max_clients;
	int					ret;
	int					sd;
	int					max_sd;
	struct sockaddr_in	addr;
	char				buf[BUF_SIZE];
	char				*msg;
	fd_set				fds;
}				t_server;
*/

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
		ft_putendl("error binding");
		return ;
	}
	ft_printf("master socket initialized  on port: %d\n", s->port);
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

void	add_new_socket(t_server *s)
{
	int i;
	
	i = -1;
	while (++i < MAX_CLIENTS)
	{
		if (s->c_sock[i] == 0)
		{
			s->c_sock[i] = s->n_sock;
			ft_printf("socket added as %d\n", i);
			break;
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
		if (write(s->n_sock, s->msg, l) != l)
			return ;
		ft_putendl("response sent");
		add_new_socket(s);
	}
}

/*
** Here we check for socket closure on the client side, if not, we perform an 
** operation based on the input, right now, an echo. soon, dispatch
*/

void	handle_existing_connections(t_server *s)
{
	int	i;

	i = -1;
	while (++i < s->max_sd && s->c_sock[i])
	{
		s->sd = s->c_sock[i];
		if ((s->ret = read(s->sd, s->buf, BUF_SIZE)) == 0)
		{
			getpeername(s->sd, (struct sockaddr*)&(s->addr), (socklen_t*)&(s->addrlen));
			ft_printf("Host disconnected, ip %s, port %d\n", inet_ntoa(s->addr.sin_addr), ntohs(s->addr.sin_port));
			close(s->sd);
			s->c_sock[i] = 0; 
		}
		else
		{
			s->buf[s->ret] = '\0';
			ft_printf("Host connected of socket: %d\nbuffer return: %d\nbuffer value: %s\n", s->sd, s->ret, s->buf);
			write(s->sd, s->buf, BUF_SIZE);
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

/*
** initialize the values needed for this test server to function
**
void	init_server(t_server *s)
{
	s->max_clients = MAX_CLIENTS;
	s->opt = TRUE;
	s->msg = ft_strdup("ECHO Daemon v1.0 \r\n");
	init_client_socks(s);
	init_master(s, port);
}

int		main (void)
{
	t_server	s;
	
	init_server(&s);
	listening(&s);
	return (0);
}
*/
