/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   users.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 21:10:16 by pstringe          #+#    #+#             */
/*   Updated: 2019/02/21 20:21:34 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void new_user(t_server *s)
{
	prompt_request(s, s->l_sock, "KIFT 1.0\nPlease enter your name: ");
	if (!s->users)
		s->users = ft_queuenw(ft_strdup(s->request.text), s->request.size);
	else
		ft_enqueue(s->users, ft_strdup(s->request.text), s->request.size);
}

void cmd_whois(t_server *s)
{
	t_list	*tmp;
	t_queue	*users;

	users = s->users;
	tmp = users->head;
	while (tmp)
	{
		s->respond(s, tmp->content, tmp->content_size);
		tmp = tmp->next;
	}
}

void delete_user(t_server *s, int socket)
{
	(void)s;
	(void)socket;
	/*
	int 	i;
	t_list *tmp;
	t_queue *users;

	i = -1;
	while (++i < idx);
	*/
	return ;
}

