/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_down_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadawson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 17:10:09 by jadawson          #+#    #+#             */
/*   Updated: 2019/01/06 17:18:41 by jadawson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	lights_down(void)
{
	system("osascript /nfs/2017/j/jadawson/Desktop/brightness/make_dim.script");
}

int		main()
{
	lights_down();
	return (0);
}
