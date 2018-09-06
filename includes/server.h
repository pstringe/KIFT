/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:05:26 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/05 20:06:42 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# define SOCK_BUF_SIZE 256

# include "libft.h"
# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>

/*
**	response object
*/

typedef struct 	s_response
{
	char 	text[SOCK_BUF_SIZE];
	size_t	size;
}				t_response;

/*
** command object for dispatch
*/

typedef struct 	s_command
{
	char			*name;
	struct s_resp	(*action)(void);
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
	int					(*connect)(struct s_server*, int, char**);
	void				(*listen)(struct s_server*);
	void				(*respond)(struct s_server*);
}				t_server;
#endif
