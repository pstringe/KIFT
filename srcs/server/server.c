/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 17:52:13 by pstringe          #+#    #+#             */
/*   Updated: 2019/02/08 19:54:38 by pstringe         ###   ########.fr       */
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
	s->connect = init_master;
	s->listen = listening;
	s->dispatch = dispatch;
	s->respond = respond;
	s->cmds = g_cmds;
	s->max_clients = MAX_CLIENTS;
	s->opt = TRUE;
	s->msg = ft_strdup("ECHO Daemon v1.0 \r\n");
	init_client_socks(s);
}

int		main(int argc, char **argv)
{
	t_server	server;

	if (argc >= 2)
	{
		server_init(&server, ft_atoi(argv[1]));
		ft_printf("initialized\n");
		server.connect(&server);
		ft_printf("connected\n");
		server.listen(&server);
		ft_printf("terminating server instance: %p\n", server);
	}
	return(0);
}
