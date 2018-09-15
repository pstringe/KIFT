/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 10:13:21 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/15 15:37:31 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H
# include "server.h"
# include <time.h>
# include "types/s_entry.h"
# include "types/s_history.h"

t_entry		*entry_new(char *speech, char *command);

#endif
