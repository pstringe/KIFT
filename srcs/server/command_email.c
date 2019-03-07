/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_email.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 21:47:23 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/06 01:53:38 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char		*email_grabber(int dst)
{
	char	*destination;

	destination = NULL;
	if (dst == 1)
		destination = ft_strdup("jadawson@student.42.us.org ");
	else if (dst == 2)
		destination = ft_strdup("pstringe@student.42.us.org ");
	else if (dst == 3)
		destination = ft_strdup("dysotoma@student.42.us.org ");
	else if (dst == 4)
		destination = ft_strdup("maljean@student.42.us.org ");
	return (destination);
}

void		cmd_email(t_server *s)
{
	char	*destination;
	char	*cmd[512];
	int		dst;
	char	*script;
	char	*msg;

	script = "python srcs/server/cmd_email.py ";
	msg = "\"Congratualations you just recieved an email from kift\" ";
	dst = ft_atoi(prompt_request(s, s->l_sock, "select person to email: \
			1, for Jamie, \
			2, for Poitier, \
			3, for Dylan, \
			4, for Malik. \
	").text);
	destination = email_grabber(dst);
	ft_bzero(cmd, 512);
	ft_strlcat((char*)cmd, script, 512);
	ft_strlcat((char*)cmd, msg, 512);
	ft_strlcat((char*)cmd, destination, 512);
	ft_strlcat((char*)cmd, "42kift@gmail.com ", 512);
	ft_strlcat((char*)cmd, "42Kiftkift", 512);
	ft_printf("email string: %s\n", cmd);
	system((const char*)cmd);
	s->respond(s, "Email has been sent\n", 21);
}
