#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

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

int		main(int argc, char **argv)
{
	int hr = 0;
	int min = 0;

	if (argc == 4)
	{
		hr = convert_hour(argv[1], argv[3]); //hour + am/pm
		min = atoi(argv[2]);
	}
	if (argc == 3) //just saying 3pm, 5pm, etc. No minute given.
	{
		int hr = convert_hour(argv[1], argv[2]); //hour + am/pm
		min = 0;
	}
	
	printf("%i min in main (line95)\n", min); //TESTING REMOVE
	printf("%i hour in main (line 95)\n", hr);//TESTING REMOVE
	kift_alarm(hr, min); //hour, minute.
}


/*
currently works with hours and minutes.
Now I just need to convert arguements for the hours.

int	tm_min;   minutes range 0 to 59
int	tm_hour;  hours range 0 to 23
*/
