/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 10:53:29 by pstringe          #+#    #+#             */
/*   Updated: 2019/02/23 01:22:37 by pstringe         ###   ########.fr       */
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
	char history[4096];

	ft_bzero(history, 4096);
	tmp = server->history.queue->head;
	while (tmp)
	{
		entry = (t_entry*)(tmp->content);
		//entry->display(server, entry);
		ft_strncat(history, "speech: ", 8 );
		ft_strncat(history, entry->speech, ft_strlen(entry->speech));
		ft_strncat(history, "\t", 1);
		ft_strncat(history, "command: ", 9);
		ft_strncat(history, entry->command, ft_strlen(entry->command));
		ft_strncat(history, "\n", 1);
		tmp = tmp->next;
	}	
	server->respond(server, history, -1);
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
	{
		history->queue = ft_queuenw((void*)(entry_new(request)), sizeof(t_entry));
		history->last_save = history->queue->head;
	}
	else
		ft_enqueue(history->queue, (void*)(entry_new(request)), sizeof(t_entry));	
}

/*
**	saves modified contents of history queue to file
*/

void	history_save(t_server *server)
{
	t_list	*tmp;
	t_entry *entry;
	

	server->history.file = open("history.csv", O_WRONLY | O_APPEND);
	tmp = server->history.last_save->next;
	while(tmp)
	{
		entry = (t_entry*)tmp->content;
		ft_dprintf(server->history.file, "%s, %s\n", entry->speech, entry->command);
		tmp = tmp->next;
	}
	close(server->history.file);
}

/*
**	retrieve history from file, enqueue within history object
*/

void	history_get(t_server *server)
{
	char	*line;
	char 	**row;

	server->history.file = open("history.csv", O_RDONLY);
	ft_printf("loading history...\n");
	while (get_next_line(server->history.file, &line) > 0)
	{
		ft_bzero(server->request.text, SOCK_BUF_SIZE);
		row = ft_strsplit(line, ',');
		if (!row[0])
			break;
		ft_memcpy(server->request.text, row[0], SOCK_BUF_SIZE);
		if (row[1] && ft_strcmp(" none", ft_strtrim(row[1])))
			server->request.command.name = ft_strdup(row[1]);
		else
			server->request.command.name = ft_strdup( "none");
		server->request.size = ft_strlen(server->request.text);
		server->history.update(server);
		ft_printf("%s, %s\n", row[0], row[1]);
	}
	server->history.last_save = server->history.queue->tail;
	close(server->history.file);
}

/*
**	initialize history object
*/

void	history_init(t_server *s)
{
	s->history.file = open("history.csv", O_CREAT);
	close(s->history.file);
	s->history.queue = NULL;
	s->history.get = history_get;
	s->history.save = history_save;
	s->history.update = history_update;
	s->history.display = history_display;
	s->history.get(s);
}
