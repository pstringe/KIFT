/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_packet.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 13:57:35 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/28 16:59:41 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_PACKET
# define S_PACKET
# define PACKET_SIZE 256
# include "KIFT.h"

typedef struct 	s_packet
{
	t_ptype type;
	char	content[PACKET_SIZE];
	int		content_size;
}				t_packet;

#endif
