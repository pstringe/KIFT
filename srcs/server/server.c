/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 17:52:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/07 14:30:20 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
**	server command dispatch table
*/

struct s_command g_cmds[NO_OF_CMDS] = {
	{"q", cmd_quit},
	{NULL, NULL}
};

/*
**	initialize server object
*/

void	server_init(t_server *s)
{
	s->connect = establish_connection;
	s->listen = listening;
	s->cmds = g_cmds;
	s->dispatch = dispatch;
	s->respond = respond;
}

int		main(int argc, char **argv)
{
	t_server	server;

	server_init(&server);
	server.connect(&server, argc, argv);
	server.listen(&server);
	return(0);
}