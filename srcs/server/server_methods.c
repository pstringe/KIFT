/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_methods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:49:30 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/20 10:02:35 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
**	This function is called to establish a connection with the client machine
*/

int		establish_connection(t_server *server, int argc, char **argv)
{
	if (argc != 2)
	{
		perror("please specify port to listen on");
		return (-1);
	}

	//initialize a socket
	if (!(server->s_sock = socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("failed to get socket descriptor");
		return (-1);
	}
	//specify address type
	server->addr.sin_family = AF_INET;
	
	server->addr.sin_addr.s_addr = INADDR_ANY;
	server->addr.sin_port = htons(server->port);
	server->addr_len = sizeof(server->addr);

	if (bind(server->s_sock, (struct sockaddr*)&(server->addr), 
				(socklen_t)sizeof(server->addr)) < 0)
	{
		perror("faild to bind port to address");
		return (-1);
	}
	if (listen(server->s_sock, 5) == -1)
		perror("server is not listening");
	else
		server->listening = 1;
	return (0);
}

/*
** A function to for writing to  the response object and sending it off
*/

void	respond(t_server *server, char *msg, size_t size)
{
	ft_bzero(server->response.txt, SOCK_BUF_SIZE);
	ft_memcpy(server->response.txt, msg, size);
	server->response.size = size;
	write(server->c_sock, server->response.txt, server->response.size);
}

/*
**	This is the called for the server to listen continuosly on the read socket and
**	having registered a valid command, exit.
*/

void	listening(t_server *server)
{
	server->c_sock = accept(server->s_sock, (struct sockaddr*)&(server->addr), (socklen_t*)&(server->addr_len));
	while (server->listening)
	{
		if (server->c_sock < 0)
			perror("did not accept");
		ft_bzero(server->request.text, SOCK_BUF_SIZE);
		if (server->request.size = read(server->c_sock, &(server->request.text), SOCK_BUF_SIZE))
		{
			ft_putendl(server->request.text);
			if (!server->dispatch(server))
				server->respond(server, "command not recognized", 22);
		}
	}
	close(server->c_sock);
}

/*
** server dispatch
**	client_input:	The buffer that is used to read from the socket descriptor
**	SOCK_BUF_SIZE:	The size of the buffer
**	server->request:	An object, attatched to the server, never reallocated,
**				only updated with new values:
**				name: 	the label for the command that is triggered by the client input
**					(since eventually there will be more than one phrase that can trigger the same command)
**					
**					TODO: come to think of it, this means I will have to update the s_cmd struct so that there is,
**				       	(1), an array of strings representing the possible triggers for a command, (2) the lable for
**					the command as it will be relected in server history, (3) a pointer to a function for the 
**					command itself.	
**				
**				action: A pointer to a function for the command that was executed, taken from the cmd object being accessed
**					It will be useful to save this incase we want to have a function that allows command repetition based
**					on history.
**					
**
*/

int		dispatch(t_server *server)
{
	int 	i;
	char 	client_input[SOCK_BUF_SIZE];
	
	//make sure this buffer is clear before using it
	ft_bzero(client_input, SOCK_BUF_SIZE);
	
	//copy over the text from the request object into the client input variable
	ft_memcpy(client_input, server->request.text, server->request.size);  
	i = -1;
	
	//itterate over each command in the dispatch table
	while (server->cmds[++i].name)
	{
		//try to match the client input to a command via the name attribute
		if (!ft_strncmp(client_input, server->cmds[i].name, ft_strlen(client_input)))
		{
			//update the name based on the the command that was resolved
			server->request.command.name = server->cmds[i].name;

			//update the action 
			server->request.command.action = server->cmds[i].action;
			
			//execute the command
			server->cmds[i].action(server);

			//Not sure why I wrote this condition. the first command in the dispatch table is quit.
			//It seems that, at some point, I decided I didn't want the quit command to log in history
			//perhaps this made it easier to debug the history functions since I didn't have to end up
			//with extra quit commands everytime I terminated the server.
			//TODO: Contemplate removing this condition, make sure it doesn't fuck anything up
			if (i)
				//update hitory with the last command executed
				server->history.update(server);
			return (1);
		}
	}
	//If none of the commands can be matched based on the input, set the resquests command name to null and update
	//the history anyway, indicating the input did not resilve to any command
	server->request.command.name = NULL;
	server->history.update(server);
	return (0);
}
