/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mic.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:09:38 by dysotoma          #+#    #+#             */
/*   Updated: 2019/03/07 11:02:33 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mic.h"
#include "libft.h"

/*
** ad creates audio recording structure - for use with ALSA functions
*/

const char		*recognize_from_microphone(ad_rec_t *ad, ps_decoder_t *ps)
{
	int16		adbuf[2048];
	uint8		utt_started;
	uint8		in_speech;
	int32		k;
	char const	*hyp;

	ad_start_rec(ad);
	ps_start_utt(ps);
	utt_started = FALSE;
	while (1)
	{
		k = ad_read(ad, adbuf, 2048);
		ps_process_raw(ps, adbuf, k, FALSE, FALSE);
		in_speech = ps_get_in_speech(ps);
		if (in_speech && !utt_started)
			utt_started = TRUE;
		if (!in_speech && utt_started)
		{
			ps_end_utt(ps);
			ad_stop_rec(ad);
			hyp = ps_get_hyp(ps, NULL);
			return (hyp);
			break ;
		}
	}
}

/*
**	reads aloud whatever string is passed to it.
**	the string must not have new line chars
*/

void			say(char *buf, int time)
{
	char cmd[4096];

	ft_bzero(cmd, 4096);
	ft_strncat(cmd, "say ", 4);
	ft_strncat(cmd, buf, ft_strlen(buf));
	ft_printf("saying: %s\n", buf);
	if (ft_strncmp(buf, "history", 7))
	{
		system(cmd);
		sleep(time);
		return ;
	}
}

/*
**	initializes pocket sphinx tools for speech recognition
*/

void			sphinx_init(t_sphinx *s)
{
	s->ad = NULL;
	s->ps = NULL;
	s->config = cmd_ln_init(NULL, ps_args(), TRUE,
		"-hmm", MODELDIR "/en-us/en-us",
		"-lm", "dict/model.lm.bin",
		"-dict", "dict/dict.dic",
		"-logfn", "/dev/null",
		NULL);
	s->ps = ps_init(s->config);
	s->ad = ad_open_dev("sysdefault", (int)cmd_ln_float32_r(s->config,
		"-samprate"));
}

int				print_error(char *str)
{
	perror(str);
	return (1);
}
