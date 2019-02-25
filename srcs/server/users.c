/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   users.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 21:10:16 by pstringe          #+#    #+#             */
/*   Updated: 2019/02/24 18:38:38 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_user	*new_user(t_server *s, char *name)
{
	t_user	*user;
	char	*ip;
	int 	port;
	
	user = malloc(sizeof(t_user));
	
	getpeername(s->sd, (struct sockaddr*)&(s->addr), (socklen_t*)&(s->addrlen));
	ip = inet_ntoa(s->addr.sin_addr);
	port = ntohs(s->addr.sin_port);

	ft_bzero(user->name, 256);
	ft_memcpy(user->name, name, ft_strlen(name));
	user->port = port;
	user->socket = s->l_sock;
	user->address = ip;
	return (user);
}

void add_user(t_server *s)
{
	t_user *user;
	
	prompt_request(s, s->l_sock, "KIFT 1.0\nPlease enter your name: ");
	user = new_user(s, s->request.text);
	if (!s->users)
		s->users = ft_queuenw(user, sizeof(t_user));
	else
		ft_enqueue(s->users, user, sizeof(t_user));
}

void cmd_whois(t_server *s)
{
	t_list	*tmp;
	t_queue	*users;
	t_user	*user;
	char	response[4096];

	users = s->users;
	tmp = users->head;
	while (tmp)
	{
		user = (t_user*)(tmp->content);
		ft_strncat(response, user->name, ft_strlen(user->name));
		ft_strncat(response, tmp->next ? ", " : "", tmp->next ? 2 : 0);
		tmp = tmp->next;
	}
	s->respond(s, response, ft_strlen(response));
}

void delete_user(t_server *s, int socket)
{
	t_queue *users;
	t_user 	*user;
	t_list  *tmp;
	t_list	*last;

	users = s->users;
	last = users->head;
	tmp = users->head;
	while(tmp)
	{
		user = (t_user*)(tmp->content);
		if (user->socket == socket)
		{
			last->next = tmp->next;
			if (tmp == users->head)
				users->head = tmp->next;
			if (tmp == users->tail)
				users->tail = last;
			free(tmp);

		}
		if (tmp != users->head)
			last = last->next;
		tmp = tmp->next;
	}
}

