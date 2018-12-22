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
		The definition for the command object may be found in includes/server/types/s_command.h
**		TODO: 	allow the first attribute to be an array of strings that way
			a command may be called via multiple names
*/

struct s_command g_cmds[NO_OF_CMDS] = {
	{"q", cmd_quit},
	{"history", cmd_history},
	{NULL, NULL}
};

/*
**	initialize server object
** 		s->port: the port number the server listens for the request on
**
**		history_init:	initializes the the properties and methods 
**				needed for the history object to function
**
**		establish_connection: 	found in server_methods.c, the function that 
**					allows the server to connect to the client
**					on the established port.
**
**		listening:	found in server_methods.c, the function which listens for
**				information written to the socket descriptor

**		s->cmds: 	a global variable representing the list of functions that
**				may be called by the server accompanied by the names by which
**				they may be called from the client. Implemented via an array 
**				of structs of type s_cmd, the type definition
**
**		dispatch:	This function reads the request sent by the server
**
**		respond:	This function which relays server output to the client via the socket descriptor
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

/*
** The main function which starts the server contains three functions:
**	server_init: initializes the values and functions vital to the operation of the server
**	server.connect: points to establish_connection() in server_methods.c
**			accepts a client device's request to connect
**	server.listen:	points to listening() in server_methods.c
**			listens for bytes written the the socket descriptionfrom the client device	
*/

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
