/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weather.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 16:51:21 by ssong             #+#    #+#             */
/*   Updated: 2018/09/14 09:00:05 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include <curl/curl.h>

struct MemoryStruct {
	char *memory;
	size_t size;
};

// contents is the returned data
// size is the size of datatype
// nmemb is number of members
// *userp is the pointer to user data structure to store.

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

	mem->memory = realloc(mem->memory, mem->size + realsize + 1);
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

char *weather_curl(void)
{
	CURL *curl_handle;
	CURLcode res;

	struct MemoryStruct chunk;

	chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
	chunk.size = 0;    /* no data at this point */ 

	curl_handle = curl_easy_init();
	curl_easy_setopt(curl_handle, CURLOPT_URL, "http://api.openweathermap.org/data/2.5/weather?zip=94555,us&units=imperial&APPID=a84567876c635d5929647ab1879c3122");
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
	res = curl_easy_perform(curl_handle);
	curl_easy_cleanup(curl_handle);
	return (chunk.memory);
}

char *parse_JSON(char *message)
{
	char *response; 
	char conditions[128];
	char temperature[128];
	int i;

	i = 0;
	message = ft_strstr(message, "description");
	message += 14;
	while (message[i] != '"')
		i++;
	ft_memcpy(conditions, message, i);
	conditions[i] = 0;
	
	message = ft_strstr(message, "temp");
	message += 6;
	ft_memcpy(temperature, message, 2);
	temperature[2] = 0;
	
	response = ft_strnew(128);
	sprintf(response, "Today's temperature is %s degrees farenheit with %s", temperature, conditions);
	return (response);
}


char *grab_weather(void)
{
	char *data;
	char *response;

	data = weather_curl();
	response = parse_JSON(data);
	return (response);
}

int main()
{
	printf("%s\n", grab_weather());
	return (0);
}
