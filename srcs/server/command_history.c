/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 16:38:12 by pstringe          #+#    #+#             */
/*   Updated: 2018/10/25 11:56:17 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

void	cmd_history(t_server *server)
{
	server->history.display(server);
	server->respond(server, "history on server\n", 18);
}
