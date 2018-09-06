/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:05:26 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/05 18:51:59 by pstringe         ###   ########.fr       */
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

typedef struct 	s_resp
{
	char *text;
	char *size;
}				t_resp;

/*
** command object for dispatch
*/

typedef struct 	s_cmd
{
	char			*name;
	struct s_resp	(*action)(void);
}				t_cmd;

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
}				t_server;
#endif
