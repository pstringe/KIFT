/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiserver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:18:30 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/06 00:08:10 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
** initialize client sockets to 0
*/

void		init_client_socks(t_server *s)
{
	int i;

	i = -1;
	while (++i < MAX_CLIENTS)
		s->c_sock[i] = 0;
}

/*
**	initialize master socket
*/

void		init_master(t_server *s)
{
	if ((s->m_sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		ft_putendl("error creating master socket");
		return ;
	}
	if (setsockopt(s->m_sock, SOL_SOCKET, SO_REUSEADDR, \
				(char *)&(s->opt), sizeof(s->opt)) < 0)
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
	ft_printf("master socket: %d, initialized on port: %d\n", \
			s->m_sock, s->port);
}

/*
**	A function to add new sockets to the fd structure. Called from
**	handel_new_connections.c
*/

void		add_child_sockets(t_server *s)
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
**	A function to add a new socket to our fd set when we get a new
**	incoming client connection. Called from handel_new_connections in
**	listening.c
*/

void		add_new_users(t_server *s)
{
	int i;

	i = -1;
	while (++i < MAX_CLIENTS)
	{
		if (s->c_sock[i] == 0)
		{
			s->c_sock[i] = s->n_sock;
			s->l_sock = s->n_sock;
			add_user(s);
			ft_printf("user, %s added on as client, %d socket %d\n", \
					s->users->tail->content, i, s->n_sock);
			s->respond(s, "User Added", 11);
			break ;
		}
	}
}

/*
**	a function to hanel server dispatch called from listenting() in
**	listening.c
*/

int			dispatch(t_server *server)
{
	int	i;

	i = -1;
	while (server->cmds[++i].name)
	{
		if (!ft_strncmp(server->request.text, server->cmds[i].name, \
					SOCK_BUF_SIZE))
		{
			server->request.command.name = server->cmds[i].name;
			server->request.command.action = server->cmds[i].action;
			server->cmds[i].action(server);
			if (i)
			{
				server->history.update(server);
				server->history.save(server);
			}
			return (1);
		}
	}
	server->request.command.name = NULL;
	server->history.update(server);
	server->history.save(server);
	return (0);
}
