/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:05:26 by pstringe          #+#    #+#             */
/*   Updated: 2019/02/06 08:44:50 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
/*
** multiserver includes /defines
*/

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#define BUF_SIZE 256
#define TRUE	1
#define FALSE	0

/*
**	will remove this eventually, just making sure it doesn't cause any problems first
*/

//#define PORT 	4000
#define MAX_CLIENTS 3

/*
**	old includes / defines
*/

# define SERVER_H
# define MAX_COMMAND_SIZE 256
# define NO_OF_CMDS 3
# define SOCK_BUF_SIZE 256
# include "libft.h"
# include <stdio.h>
# include <sys/socket.h>
# include <sys/ioctl.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/time.h>
# include "types.h"

/*
**	server methods
*/

void	respond(t_server *server, char *msg, size_t size);
int		dispatch(t_server *server);
//int		establish_connection(t_server *server, int argc);
void	init_client_socks(t_server *s);
void	init_master(t_server *s);
void	listening(t_server *server);
void	history_init(t_server *s);

/*
**	commands
*/

void	cmd_quit(t_server *server);
void	cmd_history(t_server *server);

#endif
