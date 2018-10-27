/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:05:26 by pstringe          #+#    #+#             */
/*   Updated: 2018/10/25 12:41:31 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# define MAX_COMMAND_SIZE 256
# define NO_OF_CMDS 3
# define SOCK_BUF_SIZE 256
# include "libft.h"
# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include "types/server/s_server.h"

/*
**	server methods
*/

void	respond(struct s_server *server, char *msg, size_t size);
int		dispatch(struct s_server *server);
int		establish_connection(struct s_server *server, int argc, char **argv);
void	listening(struct s_server *server);

/*
**	commands
*/

void	cmd_quit(struct s_server *server, char *client_input);
void	cmd_history(struct s_server *server);

#endif
