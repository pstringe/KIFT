/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playmusic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 10:23:05 by ssong             #+#    #+#             */
/*   Updated: 2019/03/03 02:24:04 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	play_music(char *input)
{
	char command[128];
	
	sprintf(command, "sh srcs/server/play.sh -g \"%s\"", input);
	system(command);
}

void	cmd_music(t_server *s)
{
	char *input;

	input = prompt_request(s, s->l_sock, "What would you like to play?").text;
	s->respond(s, "playing music", 13);
	play_music(input);
}

