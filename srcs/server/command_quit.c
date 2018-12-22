/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_quit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 15:37:43 by pstringe          #+#    #+#             */
/*   Updated: 2018/12/22 13:01:49 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
**	this command sends the msg, "quit" to the client, and terminates the server proccess
*/

void	cmd_quit(t_server *server)
{
	server->respond(server, "quit", 4);
	server->history.update(server);
	server->history.save(server);
	server->listening = 0;
}

