/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_server.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 10:28:39 by pstringe          #+#    #+#             */
/*   Updated: 2019/02/23 01:21:49 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_SERVER_H
# define S_SERVER_H
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
	char				buf[BUF_SIZE];
	char				*msg;
	fd_set				fds;
	int					l_sock; //intended to hold the socket that currently needs to be written to
	int					listening;
	int					port;
	t_queue				*users;

	struct sockaddr_in	addr;
	socklen_t			addr_len;
	struct s_request	request;
	struct s_response	response;
	struct s_history	history;
	struct s_command	*cmds;

	void				(*connect)(struct s_server*);
	void				(*listen)(struct s_server*);
	int					(*dispatch)(struct s_server*);
	void				(*respond)(struct s_server*, char*, int);
}				t_server;

#endif
