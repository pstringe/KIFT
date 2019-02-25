/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_user.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 14:01:50 by pstringe          #+#    #+#             */
/*   Updated: 2019/02/24 18:28:59 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_USER_H
# define S_USER_H
# include <netinet/in.h>

typedef struct	s_user
{
	char 	name[256];
	int		port;
	int		socket;
	char	*address;
}				t_user;
#endif
