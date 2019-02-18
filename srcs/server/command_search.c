/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 20:52:37 by pstringe          #+#    #+#             */
/*   Updated: 2019/02/17 21:02:01 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void cmd_search(t_server *s)
{
	s->respond(s, "search initiated", 17);
    system("open -a \"Google Chrome\" https://www.google.com/search\\\?q\\=");
}
