/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_up_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadawson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 17:10:24 by jadawson          #+#    #+#             */
/*   Updated: 2019/01/06 17:11:17 by jadawson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	lights_up(void)
{
	system("osascript /nfs/2017/j/jadawson/Desktop/brightness/make_bright.script");
}

int		main()
{
	lights_up();
	return (0);
}
