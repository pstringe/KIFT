/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_email.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 21:47:23 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/03 01:43:01 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void cmd_email(t_server *s)
{
	char *cmd[512];
	char *destination;
	int	 dst;
	char *script = "python srcs/server/cmd_email.py ";
	char *msg = "\"Congratualations you just recieved an email from kift\" ";
	char *email = "42kift@gmail.com ";
	char *psswd = "42Kiftkift";

	dst = ft_atoi(prompt_request(s, s->l_sock, "Who would you like to send an email to? You can say: \
			1, for Jaimie, \
			2, for Poitier, \
			3, for Dylan, \
			4, for Malik. \
	").text);
	
	if (dst == 1)
		destination = ft_strdup("jadawson@student.42.us.org ");
	else if (dst == 2)
		destination = ft_strdup("pstringe@student.42.us.org ");
	else if (dst == 3)
		destination = ft_strdup("dysotoma@student.42.us.org ");
	else if (dst == 4)
		destination = ft_strdup("maljean@student.42.us.org ");
	

	ft_bzero(cmd, 512);
	ft_strlcat((char*)cmd, script, 512);
	ft_strlcat((char*)cmd, msg, 512);
	ft_strlcat((char*)cmd, destination, 512);
	ft_strlcat((char*)cmd, email, 512);
	ft_strlcat((char*)cmd, psswd, 512);
	
	ft_printf("email string: %s\n", cmd);
	system((const char*)cmd);
	s->respond(s, "Email has been sent\n", 21);
}
