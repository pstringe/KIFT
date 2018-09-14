/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_command.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 10:25:33 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/14 10:39:37 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_DEFINE_H
# define S_DEFINE_H
# include "s_server.h"
/*
** dispatch table element
*/

typedef struct 	s_command
{
	char	*name;
	void	(*action)(struct s_server*, char*);
}				t_command;
#endif
