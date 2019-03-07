/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_entry.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 19:12:52 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/05 19:52:29 by jadawson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_ENTRY_H
# define S_ENTRY_H

# include "server.h"
# include "types/s_server.h"

typedef struct s_server	t_server;
typedef struct s_entry	t_entry;

struct	s_entry
{
	char		speech[SOCK_BUF_SIZE];
	char		command[MAX_COMMAND_SIZE];
	void		(*display)(t_server *, t_entry *);
};

#endif
