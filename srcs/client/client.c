/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 15:52:32 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/07 19:19:07 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mic.h"
#define SNCMP(x, y, z) ft_strncmp(x, y, z)
#define O "(null)"

/*
**	initializes input and networking properties of the client,
**	as well as the neccessary tools for speech recognition
*/

static void		client_init(int argc, char **argv, t_client *c, t_sphinx *s)
{
	ft_bzero(c->buf, CLIENT_BUF_SIZE);
	c->rr = 0;
	c->f = 1;
	c->debug_mode = !ft_strncmp(argv[1], "--debug", 7) ? 1 : 0;
	c->decoded_speech = NULL;
	if (argc < 2)
		exit(print_error("Please specify port"));
	c->sock = socket(AF_INET, SOCK_STREAM, 0);
	c->serv_addr.sin_family = AF_INET;
	c->port = ft_atoi(c->debug_mode ? argv[2] : argv[1]);
	c->serv_addr.sin_port = htons(c->port);
	c->serv_addr.sin_addr.s_addr = INADDR_ANY;
	c->con = connect(c->sock, (struct sockaddr *)&(c->serv_addr),
	sizeof(c->serv_addr));
	c->imode = 1;
	ioctl(c->sock, FIONBIO, &(c->imode));
	while ((read(c->sock, &(c->buf), CLIENT_BUF_SIZE)) < 0)
		;
	ft_putendl(c->buf);
	say(ft_strchr(c->buf, '\n') + 1, 1);
	ft_bzero(c->buf, CLIENT_BUF_SIZE);
	if (c->con < 0)
		exit(print_error("Connection error"));
	sphinx_init(s);
}

/*
**	this function obtains user input and sends it to the server
*/

static void		user_request(t_client *c, t_sphinx *s)
{
	if (!c->rr || c->f)
	{
		c->decoded_speech = NULL;
		if (c->debug_mode)
			while (getline((char**)&(c->decoded_speech), &(c->cap), stdin) < 0)
			{
			}
		else
		{
			say("Speak!", 1);
			while (!ft_strlen((c->decoded_speech =
			recognize_from_microphone(s->ad, s->ps))))
				sleep(0);
		}
		printf("You Said: %s\n", c->decoded_speech);
		ft_printf("A: sending: %s to server\n", c->decoded_speech);
		write(c->sock, ft_strtrim(c->decoded_speech),
		ft_strlen(c->decoded_speech));
		c->rr = 1;
		c->f = 0;
	}
}

/*
**	this function handels responses from the server
*/

static int		server_response(t_client *c)
{
	int ret;

	if (!c->f)
	{
		while ((ret = read(c->sock, &(c->buf), 4096)) && !SNCMP(c->buf, O, 6))
			if (!ft_strncmp(c->buf, "(null)", 6) && sleep(1))
				if ((ret = read(c->sock, &(c->buf), 4096)) >= 0)
					break ;
		if (ret < 0 && !ft_strlen(c->buf))
			return (0);
		else if (ret == 0 && (c->rr = 0))
			ft_printf("server returned empty string");
		else if (!ft_strncmp(c->buf, "quit", 4))
			exit(0);
		else
		{
			say(c->buf, 1);
			ft_bzero(c->buf, CLIENT_BUF_SIZE);
			c->rr = 0;
			c->f = 0;
		}
		ft_bzero(c->buf, CLIENT_BUF_SIZE);
	}
	return (1);
}

/*
**	a function to terminate the client
*/

static void		client_terminate(t_client *c, t_sphinx *s)
{
	ad_close(s->ad);
	close(c->sock);
}

int				main(int argc, char **argv)
{
	t_client	client;
	t_sphinx	sphinx;

	client_init(argc, argv, &client, &sphinx);
	while (1)
	{
		if (server_response(&client))
			user_request(&client, &sphinx);
	}
	client_terminate(&client, &sphinx);
	return (0);
}
