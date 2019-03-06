/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_response.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 10:23:04 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/05 18:00:11 by jadawson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_RESPONSE_H
# define S_RESPONSE_H

/*
**	response object
*/

typedef struct		s_response
{
	char			txt[SOCK_BUF_SIZE];
	size_t			size;
}					t_response;
#endif
