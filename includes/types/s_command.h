/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_command.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 10:25:33 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/05 19:29:30 by jadawson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_COMMAND_H
# define S_COMMAND_H
# include "s_server.h"

/*
** dispatch table element
*/

typedef struct	s_command
{
	char		*name;
	void		(*action)(struct s_server*);
}				t_command;
#endif
