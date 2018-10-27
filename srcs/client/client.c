/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 15:52:32 by pstringe          #+#    #+#             */
/*   Updated: 2018/10/27 15:35:09 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/client.h"

/*
** ad creates audio recording structure - for use with ALSA functions
*/

const char	*recognize_from_microphone(ad_rec_t *ad, ps_decoder_t *ps)
{
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

void	sphinx_init(t_sphinx *s)
{

	s->config = NULL;                  	// create configuration structure
	s->ad = NULL;
	s->ps = NULL;						// create pocketsphinx decoder structure

	s->config = cmd_ln_init(NULL, ps_args(), TRUE,                   // Load the configuration structure - ps_args() passes the default values
		"-hmm", MODELDIR "/en-us/en-us",                            // path to the standard english language model
		"-lm", MODELDIR "/en-us/en-us.lm.bin",                      // custom language model (file must be present)
		"-dict", MODELDIR "/en-us/cmudict-en-us.dict",              // custom dictionary (file must be present)
		"-logfn", "/dev/null",                                      // suppress log info from being sent to screen
		NULL);

	s->ps = ps_init(s->config);                                                        // initialize the pocketsphinx decoder
	s->ad = ad_open_dev("sysdefault", (int) cmd_ln_float32_r(s->config, "-samprate")); // open default microphone at default samplerate

}

int		client_connect(t_client *c)
{
	c->sock = socket(AF_INET, SOCK_STREAM, 0);
	c->serv_addr.sin_family = AF_INET;
	c->serv_addr.sin_port = htons(c->port);
	c->serv_addr.sin_addr.s_addr = INADDR_ANY;
	c->con = connect(c->sock, (struct sockaddr *)&(c->serv_addr), sizeof(c->serv_addr));
	if (c->con < 0)
	{
		perror("Connection error");
		return (-1);
	}
}

int		client_listen(t_client *c)
{
	t_sphinx	sphinx;
	char		buf[CLIENT_BUF_SIZE];
	
	sphinx = c->sphinx;
	while(1)
	{	
		sphinx.decoded_speech = NULL;
		sphinx.decoded_speech = recognize_from_microphone(sphinx.ad, sphinx.ps);      // call the function to capture and decode speech
		printf("You Said: %s\n", sphinx.decoded_speech);							  // send decoded speech to screen
		if (ft_strlen(sphinx.decoded_speech))
		{
			write(c->sock, sphinx.decoded_speech, ft_strlen(sphinx.decoded_speech));
			while (read(c->sock, &buf, CLIENT_BUF_SIZE))
				ft_putstr(buf);
		}
		else
			ft_putendl("no speech recognized");
		ft_bzero(buf, CLIENT_BUF_SIZE);
	}
}

int 	client_terminate(t_client *c)
{
	ad_close(c->sphinx.ad);
	close(c->sock);
}

int		client_init(t_client *c, int port)
{
	c->port = port;
	c->connect = client_connect;
	c->listen = client_listen;
	sphinx_init(&(c->sphinx));
	//c->request = client_request;
	c->terminate = client_terminate;
}

int 	main(int argc, char const **argv)
{
	t_client				client;					
	
	if (argc < 2)
	{
		perror("Please specify port");
		return (-1);
	}
	client_init(&client, ft_atoi(argv[1]));
	client.connect(&client);
	client.listen(&client);
	client.terminate(&client);
	return (0);
}
