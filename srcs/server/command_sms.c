/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_sms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:53:31 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/07 13:12:49 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	cmd_sms(t_server *s)
{
	char	*no;
	char	*cmd[512];
	char	*script;
	char	*body;

	no = "2094908409 ";
	script = "python srcs/server/sms.py ";
	body = "Congratulations! You just recieved an sms from KIFT";
	ft_bzero(cmd, 512);
	ft_strlcat((char*)cmd, script, 512);
	ft_strlcat((char*)cmd, no, 512);
	ft_strlcat((char*)cmd, body, 512);
	system((const char *)cmd);
	s->respond(s, "sms has been sent to poitier", 28);
}
