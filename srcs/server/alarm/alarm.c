/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alarm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:31:43 by jadawson          #+#    #+#             */
/*   Updated: 2019/03/07 16:34:09 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "server.h"

int		kift_alarm(int t)
{
	int			hr;
	int			min;
	time_t		current_time;
	struct tm	*m_t;

	t = 1;
	time(&current_time);
	m_t = localtime(&current_time);
	hr = m_t->tm_min + t >= 60 ? m_t->tm_hour + 1 : m_t->tm_hour;
	min = m_t->tm_min + t > 60 ? m_t->tm_min + t - 60 : m_t->tm_min + t;
	while ((hr != m_t->tm_hour || min != m_t->tm_min) &&
			time(&current_time) && (m_t = localtime(&current_time)))
	{
		sleep(2);
		system("clear");
		ft_printf("%i not there\n", m_t->tm_min);
		ft_printf("%i not there\n", m_t->tm_hour);
	}
	if (min == m_t->tm_min && hr == m_t->tm_hour)
	{
		ft_printf("%i is the min AT END\n", m_t->tm_min);
		ft_printf("%i is the hour AT END\n", m_t->tm_hour);
	}
	return (0);
}

void	cmd_alarm(t_server *s)
{
	int t;

	t = ft_atoi(prompt_request(s, s->l_sock,
				"Please say the number of minutes").text);
	kift_alarm(t);
	s->respond(s, "Ring Ring Ring", 15);
}
