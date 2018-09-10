/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 10:13:21 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/10 11:05:26 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H
# include "server.h"
# include <time.h>

typedef struct	s_history
{
	int			file;
	t_queue		*history;										//queue of historical entries
	void		(*init)(struct s_history);						//initializes history object
	void		(*get)(struct s_history);						//enqueues current entries within the history file
	void		(*update)(struct s_history);					//enqueues new entry
	void		(*save)(struct s_history);					//appends new entries to the end of the history file
	void 		(*display)(struct s_history/*,int options*/);	//displays the current history
}				t_history;

typedef struct	s_entry
{
	char	*recognized_speech;									//the speech sent from the server
	int		*command_id;										//the command the server selected based on the speech
	//time_t	recieved_time;									//time the packet was recieved from client
	//time_t	response_time;									//time the server sent a response
	//time_t 	time_elapsed;									//total time it took for server to respond
	
}				t_entry;
#endif
