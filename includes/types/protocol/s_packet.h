/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_packet.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 13:57:35 by pstringe          #+#    #+#             */
/*   Updated: 2018/10/25 12:33:31 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_PACKET
# define S_PACKET
# define PACKET_SIZE 256

typedef struct 	s_packet
{
	int		type;
	char	content[PACKET_SIZE];
	size_t	content_size;
}				t_packet;

#endif
