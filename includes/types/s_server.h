/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_server.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 10:28:39 by pstringe          #+#    #+#             */
/*   Updated: 2019/02/05 14:48:08 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_SERVER_H
# define S_SERVER_H
# define MAX_CLIENTS 4
# include "types/s_entry.h"
# include "types/s_command.h"
# include "types/s_request.h"
# include "types/s_response.h"
# include "types/s_history.h"

/*
**	server struct containing essential variables for communication with client 
*/

typedef struct  s_server
{
	/*
	** multiserver declarations
	*/

	int					opt;
	int					m_sock;
	int					addrlen;
	int					n_sock;
	int					c_sock[MAX_CLIENTS];
	int					activity;
	int					max_clients;
	int					ret;
	int					sd;
	int					max_sd;
	struct sockaddr_in	addr;
	char				buf[BUF_SIZE];
	char				*msg;
	fd_set				fds;
	
	/*
	**	old declarations
	*/

	/*
	int					listening;
	int					port;
	int 				ret;
	// I don't remember the neccessity of s_sock, I think I only read and write from c_sock
	int					s_sock; //prob getting rid of this
	int					c_sock; //this too 
	
	int					m_sock; //master socket (new)
	fd_set				readfds; //the set of file descriptors (new)
	int					activity; //(new)
	int					valread; //(new)
	int					sd; //(sd)
	int					client_sockets[MAX_CLIENTS]; //(new)
	int					opt;

	struct sockaddr_in	addr;
	socklen_t			addr_len;
	struct s_request	request;
	struct s_response	response;
	struct s_history	history;
	struct s_command	*cmds;
	*/

	int					(*connect)(struct s_server*, int);
	void				(*listen)(struct s_server*);
	int					(*dispatch)(struct s_server*);
	void				(*respond)(struct s_server*, char*, size_t);
}				t_server;

#endif
