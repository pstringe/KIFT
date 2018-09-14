/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_entry.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 19:12:52 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/14 10:22:26 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_ENTRY_H
# define S_ENTRY_H

typedef struct	s_entry
{
	char	*speech;									//the speech sent from the server
	char	*command;											//the command the server selected based on the speech
	//time_t	recieved_time;									//time the packet was recieved from client
	//time_t	response_time;									//time the server sent a response
	//time_t 	time_elapsed;									//total time it took for server to respond	
	void	(*display)(struct s_entry* /*options*/);
}				t_entry;

#endif
