/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lightsup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 19:37:02 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/05 22:26:19 by jadawson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	cmd_lightsup(t_server *s)
{
	system("osascript srcs/server/bright_or_dim_screen/make_bright.script");
	s->respond(s, "lights up", 9);
}
