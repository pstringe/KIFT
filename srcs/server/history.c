/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 10:53:29 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/16 18:28:51 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

/*
**	displays current contents of history queue
*/

void	history_display(t_server *server)
{
	t_list	*tmp;
	t_entry *entry;
	
	tmp = server->history.queue->head;
	while (tmp)
	{
		entry = (t_entry*)(tmp->content);
		entry->display(entry);
		tmp = tmp->next;
	}	
}

/*
**	updates current contents of history queue with new entry
*/

void	history_update(t_server *server)
{
	t_history *history;
	t_request request;

	request = server->request;
	history = &(server->history);
	if (!history->queue)
		history->queue = ft_queuenw((void*)(entry_new(request)), sizeof(t_entry));
	else
		ft_enqueue(history->queue, (void*)(entry_new(request)), sizeof(t_entry));		
}

/*
**	saves modified contents of history queue to file


void	history_save(t_history *history)
{
	t_list	*tmp;
	t_entry *entry;

	history->file = open("history.csv", O_APPEND);
	tmp = history->last_save;
	while((tmp = tmp->next))
	{
		entry = tmp->content;
		ft_dprintf(history->file, "%s, %s\n", entry->speech, entry->command);
	}
}
*/
/*
**	retrieve history from file, enqueue within history object


void	history_get(t_history *history)
{
	char	*line;
	char 	**row;

	while (get_next_line(history->file, &line) >= 0)
	{
		row = ft_strsplit(line, ',');
		history->update(history, entry_new(row[0], row[1]));
	}
	history->last_save = history->queue->tail;
	close(history->file);
}
*/
/*
**	initialize history object
*/

void	history_init(t_history *history)
{
	history->file = open("history.csv", O_CREAT);
//	history->get = history_get;
//	history->save = history_save;
	history->queue = NULL;
	history->update = history_update;
	history->display = history_display;
//	history->get(history);
}