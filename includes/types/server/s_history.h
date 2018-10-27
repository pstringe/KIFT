/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_history.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 19:15:38 by pstringe          #+#    #+#             */
/*   Updated: 2018/10/25 11:30:42 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_HISTORY_H
# define S_HISTORY_H
# include "libft.h"
# include "s_server.h"

struct s_histroy;

typedef struct	s_history
{
	int			file;
	t_queue		*queue;							//queue of historical entries
	t_list		*last_save;
	void		(*init)(struct s_server*);		//initializes history object
	void		(*get)(struct s_server*);		//enqueues current entries within the history file
	void		(*update)(struct s_server*);	//enqueues new entry
	void		(*save)(struct s_server*);		//appends new entries to the end of the history file
	void 		(*display)(struct s_server*);	//displays the current history
}				t_history;

#endif 
