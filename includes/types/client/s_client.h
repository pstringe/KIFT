/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_client.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:56:03 by pstringe          #+#    #+#             */
/*   Updated: 2018/10/27 15:14:49 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_SERVER_H
# define S_SERVER_H
# include "types/protocol/s_request.h"
# include "types/protocol/s_command.h"
# include "types/client/s_sphinx.h"

/*
** client struct containing essential variables for comunication with server
*/

typedef struct	s_client
{
	int 	con;
	int 	port;
	int 	sock;
	char 	buf[CLIENT_BUF_SIZE];
	struct  sockaddr_in serv_addr;
	struct	s_sphinx	sphinx;

	int		(*init)(struct s_client*);
	int 	(*connect)(struct s_client*);
	int		(*listen)(struct s_client*);
	int 	(*request)(struct s_client*, char*);
	int		(*terminate)(struct s_client*);
}				t_client;

#endif
