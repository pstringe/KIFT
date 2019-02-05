#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


int		pm_handle(int hr)
{
	int built_in_hour = 0;

	if (hr == 1)
		built_in_hour = 13;
	if (hr == 2)
		built_in_hour = 14;
	if (hr == 3)
		built_in_hour = 15;
	if (hr == 4)
		built_in_hour = 16;
	if (hr == 5)
		built_in_hour = 17;
	if (hr == 6)
		built_in_hour = 18;
	if (hr == 7)
		built_in_hour = 19;
	if (hr == 8)
		built_in_hour = 20;
	if (hr == 9)
		built_in_hour = 21;
	if (hr == 10)
		built_in_hour = 22;
	if (hr == 11)
		built_in_hour = 23;
	return (built_in_hour);
}

int		convert_hour(char *hr, char *am_pm)
{
	int con_hour = atoi(hr);
	int	send_am_or_pm_hour = 0;

	printf("%i converted time\n", con_hour);

	if (strcmp(am_pm, "pm") == 0)
		send_am_or_pm_hour = pm_handle(con_hour);
	if (strcmp(am_pm, "am") == 0)
		send_am_or_pm_hour = con_hour;
	printf("found am hour %i\n", con_hour);

	return(con_hour);
}



int		kift_alarm(int hr, int min)
{
	time_t currentTime;
	time(&currentTime);


	struct tm *myTime =localtime(&currentTime);
//	printf("%i\n", myTime->tm_mon);

	printf("%i is the min BEGINNING\n", myTime->tm_min);
	printf("%i is the hour BEGINNING\n", myTime->tm_hour);

	while (hr != myTime->tm_hour || min != myTime->tm_min)
	{
		time_t currentTime;
		time(&currentTime);
		struct tm *myTime =localtime(&currentTime);

		sleep (2);
		system("clear");
		printf("%i not there\n", myTime->tm_min);
		printf("%i not there\n", myTime->tm_hour);
	}
	if (min == myTime->tm_min && hr == myTime->tm_hour)
	{
		printf("%i is the min AT END\n", myTime->tm_min);
		printf("%i is the hour AT END\n", myTime->tm_hour);
	}
	return (0);
}


int		main(int argc, char **argv)
{
	int hr = 0;
	int min = 0;

	if (argc == 4)
		hr = convert_hour(argv[1], argv[3]); //hour + am/pm
	min = atoi(argv[2]);
	//kift_alarm(hr, min); //hour, minute.
}


/*
currently works with hours and minutes.
Now I just need to convert arguements for the hours.

int	tm_min;   minutes range 0 to 59
int	tm_hour;  hours range 0 to 23
*/
