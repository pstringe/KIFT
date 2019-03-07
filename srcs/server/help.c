/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:05:03 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/06 19:06:04 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	handel_it(t_server *server, char *line, char **row)
{
	char	*trim;

	if (row[1] && ft_strcmp(" none", (trim = ft_strtrim(row[1]))))
	{
		server->request.command.name = ft_strdup(trim);
		free(trim);
	}
	else
		server->request.command.name = ft_strdup("none");
	server->request.size = ft_strlen(server->request.text);
	server->history.update(server);
	free(server->request.command.name);
	ft_printf("%s, %s\n", row[0], row[1]);
	free(row[0]);
	free(row[1]);
	free(row);
	free(line);
}
