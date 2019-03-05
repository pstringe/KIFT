#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "server.h"

int		convert_hour(char *hr, char *am_pm)
{
	int con_hour = atoi(hr);
	int	send_am_or_pm_hour = 0;

	printf("%i converted time\n", con_hour); //TESTING REMOVE

	if (strcmp(am_pm, "pm") == 0)
		send_am_or_pm_hour = con_hour + 12;
	if (strcmp(am_pm, "am") == 0)
		send_am_or_pm_hour = con_hour;
	printf("found am hour (line48) %i\n", con_hour); //TESTING REMOVE

	return(send_am_or_pm_hour);
}

int		kift_alarm(int hr, int min)
{
	time_t currentTime;
	time(&currentTime);


	struct tm *myTime =localtime(&currentTime);
//	printf("%i\n", myTime->tm_mon);

	printf("%i is the min BEGINNING\n", myTime->tm_min);
	printf("%i is the hour BEGINNING\n", myTime->tm_hour);
	sleep(2);
	while (hr != myTime->tm_hour || min != myTime->tm_min)
	{
		time_t currentTime;
		time(&currentTime);
		struct tm *myTime =localtime(&currentTime);

		sleep (2);
		system("clear");
		printf("%i not there\n", myTime->tm_min); //TESTING REMOVE
		printf("%i not there\n", myTime->tm_hour);//TESTING REMOVE
	}
	if (min == myTime->tm_min && hr == myTime->tm_hour)
	{
		printf("%i is the min AT END\n", myTime->tm_min);//TESTING REMOVE
		printf("%i is the hour AT END\n", myTime->tm_hour);//TESTING REMOVE
	}
	return (0);
}

void	cmd_alarm(t_server *s)
{
	int hr = 0;
	int min = 0;
	char *hour = NULL;
	char *minute = NULL;
	char *am_pm = NULL;
	
	hour = ft_strdup(prompt_request(s, s->l_sock, "What time? Please tell me the hour.").text);
	ft_printf("test hour: %s\n", hour);
	minute = ft_strdup(prompt_request(s, s->l_sock, "Alright, Please tell me the minute").text);
	ft_printf("test minute: %s\n", minute);
	am_pm = ft_strdup(prompt_request(s, s->l_sock, "Please tell me, am or pm?").text);
	hr = convert_hour(hour, am_pm); //hour + am/pm
	min = ft_atoi(minute);
	free(hour);
	free(minute);
	kift_alarm(hr, min); //hour, minute.
	s->respond(s, "Ring Ring Ring", 15);
}


/*
currently works with hours and minutes.
Now I just need to convert arguements for the hours.

int	tm_min;   minutes range 0 to 59
int	tm_hour;  hours range 0 to 23
*/
