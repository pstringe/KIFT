/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_pic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadawson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 10:59:23 by jadawson          #+#    #+#             */
/*   Updated: 2019/03/07 11:34:23 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	cmd_team(t_server *s)
{
	system("open https://www.flickr.com/photos/162616625@N08/33410045108/in\
/dateposted-public/");
	s->respond(s, "Displaying team", 15);
}
