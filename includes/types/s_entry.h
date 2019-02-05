/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_entry.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 19:12:52 by pstringe          #+#    #+#             */
/*   Updated: 2018/12/22 12:56:52 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_ENTRY_H
# define S_ENTRY_H
# include "server.h"
# include "types/s_server.h"

typedef struct	s_server t_server;
typedef struct	s_entry t_entry;
typedef struct	s_entry
{
	char	speech[SOCK_BUF_SIZE];								//the speech sent from the server
	char	command[MAX_COMMAND_SIZE];					//the command the server selected based on the speech
	//time_t	recieved_time;									//time the packet was recieved from client
	//time_t	response_time;									//time the server sent a response
	//time_t 	time_elapsed;									//total time it took for server to respond	
	void	(*display)(t_server*, t_entry* /*options*/);
}				t_entry;


#endif