/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lightsdown.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 19:38:22 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/03 01:29:46 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	cmd_lightsdown(t_server *s)
{
	system("osascript srcs/server/bright_or_dim_screen/make_dim.script");
	s->respond(s, "lights down", 11);
}

