/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:05:26 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/06 20:12:36 by dysotoma         ###   ########.fr       */
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
# define NO_OF_CMDS 14
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

void		respond(t_server *server, char *msg, int size);
int			dispatch(t_server *server);
void		init_client_socks(t_server *s);
void		init_master(t_server *s);
void		history_init(t_server *s);
void		history_clean(t_server *s);

/*
**	prompt functions
*/

t_request	conf_request(t_server *s, int socket, char *prompt);
t_request	prompt_request(t_server *s, int socket, char *prompt);

/*
** listening functions
*/

void		listening(t_server *server);

/*
**	user functions
*/

void		add_user(t_server *s);
void		delete_user(t_server *s, int sock);
void		add_new_users(t_server *s);
void		add_child_sockets(t_server *s);

/*
**	commands
*/

void		cmd_whereis(t_server *s);
void		cmd_whois(t_server *s);
void		cmd_lightsup(t_server *server);
void		cmd_lightsdown(t_server *server);
void		cmd_sms(t_server *server);
void		cmd_music(t_server *server);
void		cmd_weather(t_server *server);
void		cmd_email(t_server *server);
void		cmd_search(t_server *server);
void		cmd_alarm(t_server *server);
void		cmd_quit(t_server *server);
void		cmd_history(t_server *server);
void		cmd_team(t_server *server);

/*
**	helper functions
*/

void		handel_it(t_server *s, char *line, char **row);

/*
** struct
*/

struct		s_memorystruct {
	char	*memory;
	size_t	size;
}			t_memorystruct;

#endif
