/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 10:53:29 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/10 11:59:18 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

/*
**	displays current contents of history queue
*/

void	history_display(t_history *history)
{
	
}

/*
**	updates current contents of history queue with new entry
*/

void	history_update()
{
}

/*
**	saves current contents of history queue to file
*/

void	history_save(t_history *history)
{

}

/*
**	retrieve history from file, enqueue within history object
*/

void	history_get(t_history *history)
{

}

/*
**	initialize history object
*/

void	history_init(t_history *history)
{
	history->file = open("history", O_CREAT);
	history->get = history_get;
	history->save = history_save;
	history->update = history_update;
	history->display = history_display;
}
