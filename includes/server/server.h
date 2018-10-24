/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:05:26 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/28 16:31:45 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# define MAX_COMMAND_SIZE 256
# define NO_OF_CMDS 3
# define SOCK_BUF_SIZE 256
# include "libft.h"
# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include "types.h"

/*
**	server methods
*/

void	respond(t_server *server, char *msg);
int		dispatch(t_server *server);
int		establish_connection(t_server *server, int argc, char **argv);
void	listening(t_server *server);

/*
**	commands
*/

void	cmd_quit(t_server *server, char *client_input);
void	cmd_history(t_server *server);

#endif
