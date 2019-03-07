/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   users.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 21:10:16 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/04 07:32:40 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
** The new user function takes a name, and returns
** a sruct containing the name and other information
** relevant to the client machine the user is connected on.
*/

t_user	*new_user(t_server *s, char *name)
{
	t_user	*user;
	char	*ip;
	int		port;

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

/*
** The add_user() function will be called whenever a new client
** connection is initiated It will prompt the user for the name
** they would like to be known as on the system, and save that
** information along with the adress, port and socket the client
** is connected on.
*/

void	add_user(t_server *s)
{
	t_user *user;

	prompt_request(s, s->l_sock, "KIFT 1.0\nPlease enter your name: ");
	user = new_user(s, s->request.text);
	if (!s->users)
		s->users = ft_queuenw(user, sizeof(t_user));
	else
		ft_enqueue(s->users, user, sizeof(t_user));
}

/*
** The whois command, when called from the client will
** cause the server to respond with a string containing
** users who are currently connected to the system
*/

void	cmd_whois(t_server *s)
{
	t_list	*tmp;
	t_queue	*users;
	t_user	*user;
	char	response[4096];

	users = s->users;
	tmp = users->head;
	ft_bzero(response, 4096);
	while (tmp)
	{
		user = (t_user*)(tmp->content);
		ft_strncat(response, user->name, ft_strlen(user->name));
		ft_printf("debug: cmd_whois:\n\tusername: %s\n", user->name);
		ft_strncat(response, tmp->next ? ", " : "", tmp->next ? 2 : 0);
		tmp = tmp->next;
	}
	s->respond(s, response, ft_strlen(response));
}

/*
** The whereis command, when called from the client, will prompt
** the user for the name of a person who is connected to the system.
** Upon recieving said name, will return the user's ip address.
*/

void	cmd_whereis(t_server *s)
{
	t_queue	*users;
	t_user	*user;
	t_list	*tmp;
	char	response[256];

	prompt_request(s, s->l_sock, "Which user would you like to locate?");
	users = s->users;
	tmp = users->head;
	ft_memcpy(response, "This user is not currently connected", 36);
	while (tmp)
	{
		user = (t_user*)(tmp->content);
		if (!ft_strncmp(user->name, s->request.text, s->request.size))
		{
			ft_bzero(response, 256);
			ft_strncat(response, "User ", 5);
			ft_strncat(response, s->request.text, s->request.size);
			ft_strncat(response, " Is located at ", 15);
			ft_strncat(response, user->address, ft_strlen(user->address));
			break ;
		}
		tmp = tmp->next;
	}
	s->respond(s, response, ft_strlen(response));
}

/*
**	A function to delete a user
*/

void	delete_user(t_server *s, int socket)
{
	t_queue	*users;
	t_user	*user;
	t_list	*tmp;
	t_list	*last;

	users = s->users;
	last = users->head;
	tmp = users->head;
	while (tmp)
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
