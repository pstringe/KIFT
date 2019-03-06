/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_history.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 19:15:38 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/05 17:54:57 by jadawson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_HISTORY_H
# define S_HISTORY_H
# include "libft.h"
# include "types/s_server.h"

struct s_histroy;

typedef struct	s_history
{
	int			file;
	t_queue		*queue;
	t_list		*last_save;
	void		(*init)(struct s_server*);
	void		(*get)(struct s_server*);
	void		(*update)(struct s_server*);
	void		(*save)(struct s_server*);
	void		(*display)(struct s_server*);
}				t_history;
#endif
