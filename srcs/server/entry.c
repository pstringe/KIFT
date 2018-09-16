/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 12:18:56 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/15 16:22:53 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "history.h"
#include "server.h"

void		entry_display(t_entry *entry)
{
	ft_printf("speech: %s\n command: %s\n", entry->speech, entry->command);
}

t_entry		*entry_new(struct s_request request)
{
	t_entry *entry;

	entry = ft_memalloc(sizeof(t_entry));
	ft_memcpy(entry->speech, request.text, request.size);
	ft_memcpy(entry->command, request.command.name, MAX_COMMAND_SIZE);
	entry->display = entry_display;

	return (entry);
}
