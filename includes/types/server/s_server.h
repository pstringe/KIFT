/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_server.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 10:28:39 by pstringe          #+#    #+#             */
/*   Updated: 2018/10/25 11:47:16 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_SERVER_H
# define S_SERVER_H
# include "s_entry.h"
# include "s_history.h"
# include "types/protocol/s_command.h"
# include "types/protocol/s_request.h"
# include "types/protocol/s_response.h"

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
	struct s_request	request;
	struct s_response	response;
	struct s_history	history;
	struct s_command	*cmds;
	int					(*connect)(struct s_server*, int, char**);
	void				(*listen)(struct s_server*);
	int					(*dispatch)(struct s_server*);
	void				(*respond)(struct s_server*, char*, size_t);
}				t_server;

#endif
