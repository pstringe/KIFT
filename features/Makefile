# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssong <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/13 19:12:17 by ssong             #+#    #+#              #
#    Updated: 2018/09/14 17:44:55 by ssong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	gcc -Wall -Werror -Wextra -o weatherexec -lcurl -L../includes/libft/ -lft weather/weather.c -I../includes/libft/.

musicexec:
	gcc -Wall -Werror -Wextra -o musicexec -L../includes/libft/ -lft music/playmusic.c -I../includes/libft/.

term:
	gcc -Wall -Werror -Wextra -o term -lcurl -L../includes/libft/ -lft search/web_search.c -I../includes/libft/.

clean:
	rm -rf weatherexec
	rm -rf musicexec
