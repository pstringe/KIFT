/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 12:18:56 by pstringe          #+#    #+#             */
/*   Updated: 2018/09/10 12:28:14 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void		entry_display(t_entry *entry)
{
	ft_printf("speech: %s\n command: %s\n", entry->speech, entry->command);
}

t_entry		*entry_new(char *speech, char *command)
{
	t_entry entry;

	entry = ft_memalloc(sizeof(t_entry));
	entry->speech = speech;
	entry->command = command;
	entry->display = entry_display;

	return (entry);
}
