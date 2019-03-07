/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_weather.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadawson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 21:29:54 by jadawson          #+#    #+#             */
/*   Updated: 2019/03/06 18:11:44 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <curl/curl.h>
#define CURLL CURL	*curl_handle

/*
** contents is the returned data
** size is the size of datatype
** nmemb is number of members
** *userp is the pointer to user data structure to store.
*/

static	size_t	writememorycallback(void *contents, size_t size, size_t nmemb,
void *userp)
{
	size_t					realsize;
	struct s_memorystruct	*mem;

	realsize = size * nmemb;
	mem = (struct s_memorystruct *)userp;
	mem->memory = realloc(mem->memory, mem->size + realsize + 1);
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
	return (realsize);
}

static char		*weather_curl(void)
{
	CURLcode				res;
	struct s_memorystruct	chunk;

	CURLL;
	chunk.memory = malloc(1);
	chunk.size = 0;
	curl_handle = curl_easy_init();
	curl_easy_setopt(curl_handle, CURLOPT_URL, "http://api.openweathermap.org/d\
ata/2.5/weather?zip=94555,us&units=imperial&APPID=a84567876c635d5929647ab1879c3\
122");
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, writememorycallback);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
	res = curl_easy_perform(curl_handle);
	curl_easy_cleanup(curl_handle);
	return (chunk.memory);
}

static char		*parse_json(char *message)
{
	char	*response;
	char	conditions[128];
	char	temperature[128];
	int		i;

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
	sprintf(response, "\"Today\'s temperature is %s degrees farenheit \
with %s\"", temperature, conditions);
	return (response);
}

void			cmd_weather(t_server *s)
{
	char	*data;
	char	*response;

	data = weather_curl();
	response = parse_json(data);
	s->respond(s, response, ft_strlen(response));
}
