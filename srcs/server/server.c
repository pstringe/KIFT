/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 17:52:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/05 20:06:38 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"



void	server_init(t_server *s)
{
	s->connect = establish_connection;
	s->listen = listening;
	//s->respond = server_respond;
}

int		main(int argc, char **argv)
{
	t_server	server;

	server_init(&server);
	server.connect(&server, argc, argv);
	server.listen(&server);
	return(0);
}
