/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alarm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadawson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:31:43 by jadawson          #+#    #+#             */
/*   Updated: 2019/03/06 20:15:35 by jadawson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "server.h"

int		convert_hour(char *hr, char *am_pm)
{
	int con_hour;
	int	send_am_or_pm_hour;

	con_hour = atoi(hr);
	send_am_or_pm_hour = 0;
	if (strcmp(am_pm, "PM") == 0)
		send_am_or_pm_hour = con_hour + 12;
	if (strcmp(am_pm, "AM") == 0)
		send_am_or_pm_hour = con_hour;
	ft_printf("found am hour (line48) %i\n", con_hour);
	return (send_am_or_pm_hour);
}

int		kift_alarm(int hr, int min)
{
	time_t		current_time;
	struct tm	*my_time;

	my_time = localtime(&current_time);
	time(&current_time);
	while (hr != my_time->tm_hour || min != my_time->tm_min)
	{
		time(&current_time);
		my_time = localtime(&current_time);
		sleep(2);
		system("clear");
		ft_printf("%i not there\n", my_time->tm_min);
		ft_printf("%i not there\n", my_time->tm_hour);
	}
	if (min == my_time->tm_min && hr == my_time->tm_hour)
	{
		ft_printf("%i is the min AT END\n", my_time->tm_min);
		ft_printf("%i is the hour AT END\n", my_time->tm_hour);
	}
	return (0);
}

void	cmd_alarm(t_server *s)
{
	int		hr;
	int		min;
	char	*hour;
	char	*minute;
	char	*am_pm;

	hour = ft_strdup(prompt_request(s, s->l_sock,
				"What time? Please tell me the hour.").text);
	ft_printf("test hour: %s\n", hour);
	minute = ft_strdup(prompt_request(s, s->l_sock,
				"Alright, Please tell me the minute").text);
	ft_printf("test minute: %s\n", minute);
	am_pm = ft_strdup(prompt_request(s, s->l_sock,
				"Please tell me, am or pm?").text);
	hr = convert_hour(hour, am_pm);
	min = ft_atoi(minute);
	free(hour);
	free(minute);
	kift_alarm(hr, min);
	s->respond(s, "Ring Ring Ring", 15);
}
