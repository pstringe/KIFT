/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 15:52:32 by pstringe          #+#    #+#             */
/*   Updated: 2019/03/01 01:07:55 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include "libft.h"
#include "mic.h"
#define CLIENT_BUF_SIZE 256

/*
** ad creates audio recording structure - for use with ALSA functions
*/

const char * recognize_from_microphone(ad_rec_t *ad, ps_decoder_t *ps){
	int16 adbuf[4096];                 // buffer array to hold audio data
	uint8 utt_started, in_speech;      // flags for tracking active speech - has speech started? - is speech currently happening?
	int32 k;                           // holds the number of frames in the audio buffer
	char const *hyp;                   // pointer to "hypothesis" (best guess at the decoded result)

    ad_start_rec(ad);                                // start recording
    ps_start_utt(ps);                                // mark the start of the utterance
    utt_started = FALSE;                             // clear the utt_started flag

    while(1) {
        k = ad_read(ad, adbuf, 4096);                // capture the number of frames in the audio buffer
        ps_process_raw(ps, adbuf, k, FALSE, FALSE);  // send the audio buffer to the pocketsphinx decoder

        in_speech = ps_get_in_speech(ps);            // test to see if speech is being detected

        if (in_speech && !utt_started) {             // if speech has started and utt_started flag is false
            utt_started = TRUE;                      // then set the flag
        }

        if (!in_speech && utt_started) {             // if speech has ended and the utt_started flag is true
            ps_end_utt(ps);                          // then mark the end of the utterance
            ad_stop_rec(ad);                         // stop recording
            hyp = ps_get_hyp(ps, NULL );             // query pocketsphinx for "hypothesis" of decoded statement
            return hyp;                              // the function returns the hypothesis
            break;                                   // exit the while loop and return to main
        }
    }
}

void 	say(char *buf)
{
	char cmd[4096];

	ft_bzero(cmd, 4096);
	ft_strncat(cmd, "say ", 4);
	ft_strncat(cmd, buf, ft_strlen(buf));
	if (fork() == 0)
		system(cmd);
	else
		return ;
	exit(0);
}

typedef struct	s_sphinx
{
	cmd_ln_t *config;
	ad_rec_t *ad;
	ps_decoder_t *ps;

}				t_sphinx;

typedef	struct	s_client
{
	int					con;
	int					rr;  // a flag to check that requests have been met with responses
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

void	sphinx_init(t_sphinx *s)
{
	//s->config = NULL;           			// create configuration structure
	s->ad = NULL;
	s->ps = NULL;           			// create pocketsphinx decoder structure
	s->config = cmd_ln_init(NULL, ps_args(), TRUE,	// Load the configuration structure - ps_args() passes the default values
		"-hmm", MODELDIR "/en-us/en-us", 			// path to the standard english language model
		"-lm", MODELDIR "/en-us/en-us.lm.bin",  	// custom language model (file must be present)
		"-dict", MODELDIR "/en-us/cmudict-en-us.dict",  // custom dictionary (file must be present)
		"-logfn", "/dev/null",  					// suppress log info from being sent to screen
		NULL);

	s->ps = ps_init(s->config);        				// initialize the pocketsphinx decoder
	s->ad = ad_open_dev("sysdefault", (int) cmd_ln_float32_r(s->config, "-samprate")); // open default microphone at default samplerate
}

void	client_init(int argc, char **argv, t_client *c, t_sphinx *s)
{
	c->rr = 0;
	c->f = 1;
	c->debug_mode = !ft_strncmp(argv[1], "--debug", 7) ? 1 : 0;
	c->decoded_speech = NULL;
	if (argc < 2)
	{
		perror("Please specify port");
		exit(1);
	}
	c->sock = socket(AF_INET, SOCK_STREAM, 0);
	c->serv_addr.sin_family = AF_INET;
	c->port = ft_atoi(c->debug_mode ? argv[2] : argv[1]);
	c->serv_addr.sin_port = htons(c->port);
	c->serv_addr.sin_addr.s_addr = INADDR_ANY;
	c->con = connect(c->sock, (struct sockaddr *)&(c->serv_addr), sizeof(c->serv_addr));
	c->imode = 1;
	ioctl(c->sock, FIONBIO, &(c->imode));
	while(read(c->sock, &(c->buf), CLIENT_BUF_SIZE) < 0);
	ft_putendl(c->buf);
	ft_bzero(c->buf, CLIENT_BUF_SIZE);
	if (c->con < 0)
	{
		perror("Connection error");
		exit(1);
	}
	sphinx_init(s);
}

void	user_request(t_client *c, t_sphinx *s)
{

	if (!c->rr || c->f)
	{
		if (c->debug_mode)
			while (getline((char**)&(c->decoded_speech), &(c->cap), stdin) < 0);
		else
			c->decoded_speech = recognize_from_microphone(s->ad, s->ps);  // call the function to capture and decode speech
		printf("You Said: %s\n", c->decoded_speech);								// send decoded speech to screen
		ft_printf("A: sending: %s to server\n", c->decoded_speech);
		write(c->sock, ft_strtrim(c->decoded_speech), ft_strlen(c->decoded_speech));
		c->rr = 1;
		c->f = 0;
	}
}

int		server_response(t_client *c)
{
	if (!c->f)
	{
		int ret;
		
		ft_printf("B: about to read from server\n");
		if ((ret = read(c->sock, &(c->buf), 4096)) < 0)
		{
			ft_printf("waiting on server\n");
			return (0);
		}
		else if (ret == 0 && (c->rr = 0))
			ft_printf("server returned empty string");
		else
		{
			say(c->buf);
			c->rr = 0;
			c->f = 0;
		}
		ft_printf("C: read %d bytes from %s from server\n", ret, c->buf);
		ft_bzero(c->buf, CLIENT_BUF_SIZE);
		ft_printf("D: cleared buffer\n");
	}
	return (1);
}

void	client_terminate(t_client *c, t_sphinx *s)
{
	ad_close(s->ad);
	close(c->sock);
}

int		main(int argc, char **argv)
{

	t_client	client;
	t_sphinx	sphinx;

	client_init(argc, argv, &client, &sphinx);
	while(1){
		if(!server_response(&client))
			continue ;
		user_request(&client, &sphinx);
	}	
	client_terminate(&client, &sphinx);
	return (0);
}
