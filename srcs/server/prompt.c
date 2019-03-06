/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 00:05:51 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/06 00:08:15 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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
