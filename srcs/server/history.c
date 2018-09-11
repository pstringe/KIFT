/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 10:53:29 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/10 15:17:47 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

/*
**	displays current contents of history queue
*/

void	history_display(t_history *history)
{
	t_list	*tmp;
	t_entry *entry;
	
	tmp = history->queue->head;
	while (tmp)
	{
		entry = tmp->content;
		entry->display(entry);
	}	
}

/*
**	updates current contents of history queue with new entry
*/

void	history_update(t_history *history, t_entry *entry)
{
	if (!history->queue)
		history->queue = ft_queuenw((void*)entry, sizeof(t_entry));
	else
		ft_enqueue(history->queue, (void*)entry, sizeof(t_entry));		
}

/*
**	saves current contents of history queue to file
*/

void	history_save(t_history *history)
{
	t_list	*tmp;
	t_entry *entry;
	char	*row;

	history->file = open("history.csv", 0_WRONLY);
	tmp = history->last_save->next;
	while(tmp)
	{

	}
}

/*
**	retrieve history from file, enqueue within history object
*/

void	history_get(t_history *history)
{
	char	*line;
	char 	**row;

	while (get_next_line(&line, history->file) >= 0)
	{
		row = ft_strsplit(line, ',')
		history->update(history, entry_new(row[0], row[1]));
	}
	history->last_save = tail;
	close(history->file)
}

/*
**	initialize history object
*/

void	history_init(t_history *history)
{
	history->file = open("history.csv", O_CREAT);
	history->get = history_get;
	history->save = history_save;
	history->update = history_update;
	history->display = history_display;
	history->get(history);
}
