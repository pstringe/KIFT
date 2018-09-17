/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 17:52:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/17 15:23:53 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
**	server command dispatch table
*/

struct s_command g_cmds[NO_OF_CMDS] = {
	{"q", cmd_quit},
	{"history", cmd_history},
	{NULL, NULL}
};

/*
**	initialize server object
*/

void	server_init(t_server *s, int port)
{
	s->port = port;
	history_init(s);
	s->connect = establish_connection;
	s->listen = listening;
	s->cmds = g_cmds;
	s->dispatch = dispatch;
	s->respond = respond;
}

int		main(int argc, char **argv)
{
	t_server	server;

	server_init(&server, ft_atoi(argv[1]));
	//ft_printf("initialized\n");
	server.connect(&server, argc, argv);
	ft_printf("connected\n");
	server.listen(&server);
	ft_printf("terminating server instance: %p\n", server);
	return(0);
}
