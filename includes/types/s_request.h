/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_request.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 14:51:14 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/05 20:46:22 by jadawson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_REQUEST_H
# define S_REQUEST_H
# include "server.h"
# include "types/s_command.h"

typedef struct			s_request
{
	int					type;
	char				text[BUF_SIZE];
	struct s_command	command;
	int					size;
}						t_request;

#endif
