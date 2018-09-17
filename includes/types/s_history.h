/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_history.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 19:15:38 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/16 19:52:05 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_HISTORY_H
# define S_HISTORY_H
# include "libft.h"
# include "types/s_server.h"

struct s_histroy;

typedef struct	s_history
{
	int			file;
	t_queue		*queue;											//queue of historical entries
	t_list		*last_save;
	void		(*init)(struct s_history*);						//initializes history object
	void		(*get)(struct s_history*);						//enqueues current entries within the history file
	void		(*update)(struct s_server*);					//enqueues new entry
	void		(*save)(struct s_server*);						//appends new entries to the end of the history file
	void 		(*display)(struct s_history* /*,int options*/);	//displays the current history
}				t_history;

#endif 
