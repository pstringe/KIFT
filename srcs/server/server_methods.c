/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiserver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:18:30 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/05 22:28:57 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
** initialize client sockets to 0
*/

void		init_client_socks(t_server *s)
{
	int i;

	i = -1;
	while (++i < MAX_CLIENTS)
		s->c_sock[i] = 0;
}

/*
**	initialize master socket
*/

void		init_master(t_server *s)
{
	if ((s->m_sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		ft_putendl("error creating master socket");
		return ;
	}
	if (setsockopt(s->m_sock, SOL_SOCKET, SO_REUSEADDR, \
				(char *)&(s->opt), sizeof(s->opt)) < 0)
	{
		ft_putendl("error setsockopt");
		return ;
	}
	s->addr.sin_family = AF_INET;
	s->addr.sin_addr.s_addr = INADDR_ANY;
	s->addr.sin_port = htons(s->port);
	if (bind(s->m_sock, (struct sockaddr *)&s->addr, sizeof(s->addr)) < 0)
	{
		ft_printf("error binding, error code: %d\n", errno);
		exit(1);
	}
	ft_printf("master socket: %d, initialized on port: %d\n", \
			s->m_sock, s->port);
}

/*
**	A function to add new sockets to the fd structure. Called from
**	handel_new_connections.c
*/

void		add_child_sockets(t_server *s)
{
	int i;

	i = -1;
	while (++i < MAX_CLIENTS)
	{
		s->sd = s->c_sock[i];
		if (s->sd > 0)
			FD_SET(s->sd, &(s->fds));
		if (s->sd > s->max_sd)
			s->max_sd = s->sd;
	}
}

/*
**	A function to add a new socket to our fd set when we get a new
**	incoming client connection. Called from handel_new_connections in
**	listening.c
*/

void		add_new_users(t_server *s)
{
	int i;

	i = -1;
	while (++i < MAX_CLIENTS)
	{
		if (s->c_sock[i] == 0)
		{
			s->c_sock[i] = s->n_sock;
			s->l_sock = s->n_sock;
			add_user(s);
			ft_printf("user, %s added on as client, %d socket %d\n", \
					s->users->tail->content, i, s->n_sock);
			s->respond(s, "User Added", 11);
			break ;
		}
	}
}

/*
**	Here, we accept an incoming connection on the master socket and return a
**	a new socket to manage connections to this particular client.
*/

void		handle_new_connections(t_server *s)
{
	int	l;

	l = ft_strlen(s->msg);
	if (FD_ISSET(s->m_sock, &(s->fds)))
	{
		if ((s->n_sock = accept(s->m_sock, (struct sockaddr *)&(s->addr), \
						(socklen_t *)&(s->addr))) < 0)
			return ;
		if (fcntl(s->n_sock, F_SETFL, O_NONBLOCK) < 0)
			return ;
		ft_putendl("New Connection");
		add_new_users(s);
	}
}

/*
**	A function to for writing to  the response object and sending it off
*/

void		respond(t_server *server, char *msg, int size)
{
	if (size == -1)
		size = ft_strlen(msg);
	ft_bzero(server->response.txt, SOCK_BUF_SIZE);
	ft_memcpy(server->response.txt, msg, size);
	server->response.size = size;
	ft_printf("writing response of size: %d bytes\nresponse sample: \
			%.30s ...\n", size, server->response.txt);
	write(server->l_sock, server->response.txt, server->response.size);
}

/*
**	a function to hanel server dispatch called from listenting() in
**	listening.c
*/

int			dispatch(t_server *server)
{
	int	i;

	i = -1;
	while (server->cmds[++i].name)
	{
		if (!ft_strncmp(server->request.text, server->cmds[i].name, \
					SOCK_BUF_SIZE))
		{
			server->request.command.name = server->cmds[i].name;
			server->request.command.action = server->cmds[i].action;
			server->cmds[i].action(server);
			if (i)
			{
				server->history.update(server);
				server->history.save(server);
			}
			return (1);
		}
	}
	server->request.command.name = NULL;
	server->history.update(server);
	server->history.save(server);
	return (0);
}

/*
**	a function to allow controle over which buffer the request is stored in
**	this is to keep the program from trying to execute upon queries related
**	to argument resolution.
*/

void		init_prompt(t_server *s, int sock, char *prompt, t_request *req)
{
	respond(s, !prompt ? "(null)" : prompt, !prompt ? 6 : ft_strlen(prompt));
	ft_bzero(req->text, BUF_SIZE);
	while ((req->size = read(sock, &(req->text), BUF_SIZE)) < 0)
		if (req->size == 0)
			break ;
}

/*
**	a function to handel confirmation during resolution of speech arguments
*/
#define CHECK_IF_CONF_QUESTION	ft_strncmp(prompt, "did you mean to say: ", 21)
#define CHECK_IF_CONF_PROMPT	ft_strncmp(prompt, "Please say, yes or no.", 22)

t_request	conf_request(t_server *s, int socket, char *prompt)
{
	char *speech;
	char *req;

	init_prompt(s, socket, prompt, &(s->conf));
	if (!prompt)
		return (s->request);
	speech = ft_strdup(s->request.text);
	req = ft_strjoin("did you mean to say: ", s->conf.text);
	if (CHECK_IF_CONF_QUESTION && CHECK_IF_CONF_PROMPT)
		return (conf_request(s, s->l_sock, req));
	if (!ft_strncmp(s->conf.text, "YES", 3))
	{
		ft_bzero(s->request.text, SOCK_BUF_SIZE);
		ft_memcpy(s->request.text, speech, ft_strlen(speech));
		s->request.size = ft_strlen(speech);
		free(speech);
		free(req);
		return (s->request);
	}
	else if (!ft_strncmp(s->conf.text, "NO", 2))
		return (prompt_request(s, s->l_sock, "Ok, what did you mean to say?"));
	else
		conf_request(s, s->l_sock, "Please say, yes or no.");
	return (s->request);
}

/*
**	A function to prompt the client for a certain response Eventually,
** I may pass a function pointer to handel the request, but this will do for now
*/

t_request	prompt_request(t_server *s, int socket, char *prompt)
{
	char *speech;
	char *req;

	init_prompt(s, socket, prompt, &(s->request));
	if (!prompt)
		return (s->request);
	speech = ft_strdup(s->request.text);
	req = ft_strjoin("did you mean to say: ", s->request.text);
	if (ft_strncmp(prompt, "did you mean to say: ", 21))
		return (conf_request(s, s->l_sock, req));
	return (s->request);
}
