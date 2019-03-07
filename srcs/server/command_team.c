/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_pic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadawson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 10:59:23 by jadawson          #+#    #+#             */
/*   Updated: 2019/03/04 21:12:11 by jadawson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void cmd_team(t_server *s)
{
	s->respond(s, "Displaying team", 15);
	system("open https://www.flickr.com/photos/162616625@N08/33410045108/in\
/dateposted-public/");
}