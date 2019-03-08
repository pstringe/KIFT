/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listening.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 22:26:41 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/07 16:25:44 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
**	this funciton is called from remove_clients in
**	users.c to handel client removal.
*/

void		remove_client(t_server *s, int *i)
{
	char		*ip;
	uint16_t	port;

	ip = inet_ntoa(s->addr.sin_addr);
	port = ntohs(s->addr.sin_port);
	getpeername(s->sd, (struct sockaddr*)&(s->addr), (socklen_t*)&(s->addrlen));
	delete_user(s, s->c_sock[*i]);
	ft_printf("Host disconnected, ip %s, port %d\n", ip, port);
	close(s->c_sock[*i]);
	s->c_sock[*i] = 0;
}

/*
**	A function to hadel responses for existing clients called from
**	handel_existing_connections is server_methods.c
*/

void		handel_response(t_server *s)
{
	char	*req;

	req = NULL;
	s->l_sock = s->sd;
	if (s->request.size)
	{
		req = ft_strjoin("did you mean to say: ", s->request.text);
		conf_request(s, s->l_sock, req);
		free(req);
		ft_putendl(s->request.text);
		if (ft_strncmp(s->request.text, "(null)", 6) &&
				!s->dispatch(s) && s->request.size > 0)
			s->respond(s, "command not recognized", 22);
	}
}

/*
**	Here, we accept an incoming connection on the master socket and return a
**	a new socket to manage connections to this particular client.
*/

void		handle_new_connections(t_server *s)
{
	int	l;

	l = ft_strlen(s->msg);
	if (FD_ISSET(s->m_sock, &(s->fds)))
	{
		if ((s->n_sock = accept(s->m_sock, (struct sockaddr *)&(s->addr), \
						(socklen_t *)&(s->addr))) < 0)
			return ;
		if (fcntl(s->n_sock, F_SETFL, O_NONBLOCK) < 0)
			return ;
		ft_putendl("New Connection");
		add_new_users(s);
	}
}

/*
** Here we check for socket closure on the client side,
** if not, we perform an operation based on the input ( dispatch() )
*/

void		handle_existing_connections(t_server *s)
{
	int		i;

	i = -1;
	while (++i < s->max_sd && s->c_sock[i])
	{
		s->sd = s->c_sock[i];
		if (!prompt_request(s, s->sd, NULL).size)
			remove_client(s, &i);
		else if (s->sd < 0)
			perror("socket descriptor: sd, returns less than 0\n");
		else
			handel_response(s);
	}
}

/*
**	listen for incoming connections on master socket, determine whether they
**	come from new or existing clients, and act accordingly
*/

void		listening(t_server *s)
{
	if (listen(s->m_sock, 3) < 0)
		return ;
	s->addrlen = sizeof(s->addr);
	ft_putendl("waiting for connections");
	while (TRUE)
	{
		FD_ZERO(&(s->fds));
		ft_printf("debug: zeroed out fd struct\n");
		FD_SET(s->m_sock, &(s->fds));
		ft_printf("debug: set socket descriptors\n");
		s->max_sd = s->m_sock;
		ft_printf("debug: set max descriptor\n");
		add_child_sockets(s);
		ft_printf("debug: added child sockets\n");
		s->activity = select(s->max_sd + 1, &(s->fds), NULL, NULL, NULL);
		ft_printf("debug: select, returned %d file descriptors\n", s->activity);
		if (s->activity < 0 && errno != EINTR)
			ft_printf("select error\n");
		handle_new_connections(s);
		ft_printf("debug: handeled new connections\n");
		handle_existing_connections(s);
		ft_printf("debug: handeled existing connections\n");
	}
	return ;
}
