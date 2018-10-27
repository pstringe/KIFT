/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_request.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 14:51:14 by pstringe          #+#    #+#             */
/*   Updated: 2018/10/25 11:35:05 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_REQUEST_H
# define S_REQUEST_H
# include "../../server/server.h"
# include "s_command.h"

typedef struct 	s_request
{
	int					type;
	char				text[SOCK_BUF_SIZE];
	struct s_command	command;
	int 				size;
}				t_request;

#endif
