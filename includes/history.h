/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 10:13:21 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/12 12:50:55 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H
# include "server.h"
# include <time.h>

typedef struct	s_entry
{
	char	*speech;									//the speech sent from the server
	char	*command;											//the command the server selected based on the speech
	//time_t	recieved_time;									//time the packet was recieved from client
	//time_t	response_time;									//time the server sent a response
	//time_t 	time_elapsed;									//total time it took for server to respond	
	void	(*display)(struct s_entry* /*options*/);
}				t_entry;

typedef struct	s_history
{
	int			file;
	t_queue		*queue;											//queue of historical entries
	t_list		*last_save;
	void		(*init)(struct s_history*);						//initializes history object
	void		(*get)(struct s_history*);						//enqueues current entries within the history file
	void		(*update)(struct s_history*, struct s_entry*);					//enqueues new entry
	void		(*save)(struct s_history*);						//appends new entries to the end of the history file
	void 		(*display)(struct s_history* /*,int options*/);	//displays the current history
}				t_history;

t_entry		*entry_new(char *speech, char *command);
#endif
