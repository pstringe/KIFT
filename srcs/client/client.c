/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 15:52:32 by pstringe          #+#    #+#             */
/*   Updated: 2019/02/22 21:37:35 by pstringe         ###   ########.fr       */
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

int main(int argc, char const **argv)
{
	int					con;
	int					port;
	int					sock;
	int					debug_mode;
	size_t				cap;
	char				buf[CLIENT_BUF_SIZE];
	struct sockaddr_in 	serv_addr;
	int 				imode;

	//set debug mode to true if the option is set
	debug_mode = !ft_strncmp(argv[1], "--debug", 7) ? 1 : 0;
	cmd_ln_t *config = NULL;           // create configuration structure
	ad_rec_t *ad = NULL;
	ps_decoder_t *ps = NULL;           // create pocketsphinx decoder structure
	char const *decoded_speech = NULL;

	if (argc < 2)
	{
		perror("Please specify port");
		return (-1);
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	port = ft_atoi(debug_mode ? argv[2] : argv[1]);
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	con = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	read(sock, &buf, CLIENT_BUF_SIZE);
	ft_putendl(buf);
	ft_bzero(buf, CLIENT_BUF_SIZE);

	if (con < 0)
	{
		perror("Connection error");
		return (-1);
	}

	config = cmd_ln_init(NULL, ps_args(), TRUE,                   // Load the configuration structure - ps_args() passes the default values
		"-hmm", MODELDIR "/en-us/en-us",                            // path to the standard english language model
		"-lm", MODELDIR "/en-us/en-us.lm.bin",                      // custom language model (file must be present)
		"-dict", MODELDIR "/en-us/cmudict-en-us.dict",              // custom dictionary (file must be present)
		"-logfn", "/dev/null",                                      // suppress log info from being sent to screen
		NULL);

	ps = ps_init(config);                                                        // initialize the pocketsphinx decoder
	ad = ad_open_dev("sysdefault", (int) cmd_ln_float32_r(config, "-samprate")); // open default microphone at default samplerate

	while(1){
		imode = 1;
		ioctl(sock, FIONBIO, &imode);
		if (debug_mode)
			while (!getline((char**)&decoded_speech, &cap, stdin));
		else
			decoded_speech = recognize_from_microphone(ad, ps);  // call the function to capture and decode speech
		printf("You Said: %s\n", decoded_speech);								// send decoded speech to screen
		ft_printf("A: sending: %s to server\n", decoded_speech);
		write(sock, ft_strtrim(decoded_speech), ft_strlen(decoded_speech));
		int ret;
		ft_printf("B: about to read from server\n");
		if ((ret = read(sock, &buf, 4096)) < 0)
			ft_printf("error with read\n");
		else if (ret == 0)
			ft_printf("nothing returned");
		else
		{
			ft_putendl(buf);
		}
		ft_printf("C: read %d bytes from %s from server\n", ret, buf);
		ft_bzero(buf, CLIENT_BUF_SIZE);
		ft_printf("D: cleared buffer\n");
	}	
	ad_close(ad);
	close(sock);
	return (0);
}
