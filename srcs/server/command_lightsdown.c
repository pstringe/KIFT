/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_down_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadawson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 17:10:09 by jadawson          #+#    #+#             */
/*   Updated: 2019/03/06 18:43:15 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	cmd_lightsdown(t_server *s)
{
	call_cmd("osascript srcs/server/bright_or_dim_screen/make_dim.script");
}
