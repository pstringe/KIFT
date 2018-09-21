/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 10:13:21 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/15 16:16:51 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H
# include "server.h"
# include <time.h>
# include "types/s_entry.h"
# include "types/s_history.h"
# include "types/s_request.h"

t_entry		*entry_new(struct s_request);

#endif
