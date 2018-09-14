/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 15:52:32 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/13 17:04:49 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "libft.h"
#define CLIENT_BUF_SIZE 256

int main(int argc, char const **argv)
{
	int					con;
	int					port;
	int					sock;
	char				buf[CLIENT_BUF_SIZE];
	struct sockaddr_in 	serv_addr;

	if (argc < 3)
	{
		perror("Please specify port and msg");
		return (-1);
	}
	sock = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	port = ft_atoi(argv[1]);
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	con = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (con < 0)
	{
		perror("Connection error");
		return (-1);
	}
	int i;
	i = 1;
	while (++i < argc)
	{
		write(sock, argv[i], ft_strlen(argv[i]));
		read(sock, &buf, BUFF_SIZE);
		ft_putendl(buf);
	}
	close(sock);
	return (0);
}
