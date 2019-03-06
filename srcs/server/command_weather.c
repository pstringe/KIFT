/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_weather.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadawson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 21:29:54 by jadawson          #+#    #+#             */
/*   Updated: 2019/03/06 00:44:19 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <curl/curl.h>

struct			memory_struct {
	char		*memory;
	size_t		size;
};

static size_t	write_mem_callback(void *contents,
	size_t size, size_t nmemb, void *userp)
{
	size_t	realsize;
	struct	memory_struct *mem;

	mem = NULL;
	mem = (struct memory_struct *)userp;
	realsize = size * nmemb;
	mem->memory = realloc(mem->memory, mem->size + realsize + 1);
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
	return (realsize);
}

char *weather_curl(void)
{
	CURL 			*curl_handle;
	CURLcode		res;

	struct memory_struct chunk;

	chunk.memory = malloc(1);
	chunk.size = 0;
	curl_handle = curl_easy_init();
	curl_easy_setopt(curl_handle, CURLOPT_URL, \
			"http://api.openweathermap.org/data/2.5/weather?zip=94555,\
us&units=imperial&APPID=a84567876c635d5929647ab1879c3122");
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_mem_callback);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
	res = curl_easy_perform(curl_handle);
	curl_easy_cleanup(curl_handle);
	return (chunk.memory);
}

char	*parse_json(char *message)
{
	char		*response;
	char 		cond[128];
	char 		temp[128];
	int 		i;

	i = 0;
	message = ft_strstr(message, "description");
	message += 14;
	while (message[i] != '"')
		i++;
	ft_memcpy(cond, message, i);
	cond[i] = 0;
	message = ft_strstr(message, "temp");
	message += 6;
	ft_memcpy(temp, message, 2);
	temp[2] = 0;
	response = ft_strnew(128);
	sprintf(response, "\"Today\'s temp is %s degrees with %s\"", temp, cond);
	return (response);
}

void	cmd_weather(t_server *s)
{
	char	*data;
	char	*response;

	data = weather_curl();
	response = parse_json(data);
	s->respond(s, response, ft_strlen(response));
}
