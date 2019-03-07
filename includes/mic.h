/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mic.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 17:45:14 by jadawson          #+#    #+#             */
/*   Updated: 2019/03/07 10:49:13 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIC_H
# define MIC_H
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/ioctl.h>
# include <netinet/in.h>
# include <pocketsphinx.h>
# include <sphinxbase/ad.h>
# include <sphinxbase/err.h>
# define CLIENT_BUF_SIZE 4096

typedef struct	s_sphinx
{
	cmd_ln_t *config;
	ad_rec_t *ad;
	ps_decoder_t *ps;

}				t_sphinx;

typedef	struct	s_client
{
	int					con;
	int					rr;
	int					f;
	int					port;
	int					sock;
	int					debug_mode;
	size_t				cap;
	char				buf[CLIENT_BUF_SIZE];
	struct sockaddr_in 	serv_addr;
	int 				imode;
	char const			*decoded_speech;
}				t_client;

const char	*recognize_from_microphone(ad_rec_t *ad, ps_decoder_t *ps);
int			print_error(char *str);
void 		say(char *buf, int time);
void		sphinx_init(t_sphinx *s);
#endif
