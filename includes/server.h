/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:05:26 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/08 14:13:59 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# define SOCK_BUF_SIZE 256
# define NO_OF_CMDS
# include "libft.h"
# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>

struct s_server;

/*
**	response object
*/

typedef struct 	s_response
{
	char 	txt[SOCK_BUF_SIZE];
	size_t	size;
}				t_response;

/*
** dispatch table element
*/

typedef struct 	s_command
{
	char	*name;
	void	(*action)(struct s_server*, char*);
}				t_command;

/*
**	server struct containing essential variables for communication with client 
*/

typedef struct  s_server
{
	int					listening;
	int					port;
	int 				ret;
	int					s_sock;
	int					c_sock;
	struct sockaddr_in	addr;
	socklen_t			addr_len;
	struct s_response	response;
	struct s_command	*cmds;
	int					(*connect)(struct s_server*, int, char**);
	void				(*listen)(struct s_server*);
	int					(*dispatch)(struct s_server*, char*);
	void				(*respond)(struct s_server*, char*, size_t);
}				t_server;

/*
**	server methods
*/

void	respond(t_server *server, char *msg, size_t size);
int		dispatch(t_server *server, char *client_input);
int		establish_connection(t_server *server, int argc, char **argv);
void	listening(t_server *server);

/*
**	commands
*/

void	cmd_quit(t_server *server, char *client_input);

#endif
