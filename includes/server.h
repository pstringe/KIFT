/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:05:26 by pstringe          #+#    #+#             */
/*   Updated: 2019/02/18 19:44:17 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H

/*
** defines
*/

# define SERVER_H
# define BUF_SIZE 4096
# define TRUE	1
# define FALSE	0
# define MAX_CLIENTS 3
# define MAX_COMMAND_SIZE 256
# define NO_OF_CMDS 11
# define SOCK_BUF_SIZE 4096

/*
** includes
*/

# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
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

void		respond(t_server *server, char *msg, size_t size);
int			dispatch(t_server *server);
//int		establish_connection(t_server *server, int argc);
void		init_client_socks(t_server *s);
void		init_master(t_server *s);
void		listening(t_server *server);
void		history_init(t_server *s);
t_request	prompt_request(t_server *s, int socket, char *prompt);

/*
**	commands
*/

void	cmd_lightsup(t_server *server);
void	cmd_lightsdown(t_server *server);
void	cmd_sms(t_server *server);
void	cmd_music(t_server *server);
void	cmd_weather(t_server *server);
void	cmd_email(t_server *server);
void 	cmd_search(t_server *server);
void 	cmd_alarm(t_server *server);
void	cmd_quit(t_server *server);
void	cmd_history(t_server *server);

#endif
