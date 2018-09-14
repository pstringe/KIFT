/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playmusic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 10:23:05 by ssong             #+#    #+#             */
/*   Updated: 2018/09/14 10:45:50 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	play_music(char *input)
{
	char command[128];
	
	input += 5;
	sprintf(command, "~/Documents/KIFT/features/music/play.sh -g %s", input);
	system(command);
}

int main()
{
	char input[128] = "play daft punk";
	play_music(input);
	return (0);
}
