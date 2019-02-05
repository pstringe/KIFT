#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


int		main()
{
	time_t currentTime;
	time(&currentTime);

	int min = 19;
	int hr = 13;

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


/*
currently works with hours and minutes.
Now I just need to convert arguements for the hours.

int	tm_min;   minutes range 0 to 59
int	tm_hour;  hours range 0 to 23
*/
