#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pstringe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/02 14:49:53 by pstringe          #+#    #+#              #
#    Updated: 2019/03/06 19:10:44 by pstringe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = KIFT
CLIENT = client
SERVER = server
INCD = ./includes/

LIB = libft.a

LIBD = $(INCD)libft/
SINC = $(INCD)

SSRCD = ./srcs/server/
CSRCD = ./srcs/client/

SSRCS = server\
		server_methods\
		prompt\
		listening\
		users\
		history\
		entry\
		alarm/alarm\
		bright_or_dim_screen/command_lightsup\
		bright_or_dim_screen/command_lightsdown\
		command_music\
		command_weather\
		command_sms\
		command_email\
		command_search\
		command_history\
		command_quit\
		command_team\
		help

MSRCS = server\
		multiserver\
		history\
		entry\
		command_history\
		command_quit

CSRCS = client\
		mic

SOBJS = $(patsubst $(SSRCD)%, %.o, $(SSRCS))
COBJS = $(patsubst $(CSRCD)%, %.o, $(CSRCS))

CFLAGS = -Wall -Werror -Wextra
DFLAGS = -g
SFLAGS = -fsanitize=address -fno-omit-frame-pointer
PFLAGS = -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" \
		 `pkg-config --cflags --libs pocketsphinx sphinxbase`

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(SERVER) : $(INCD)$(LIB)
	$(CC) $(CFLAGS) -o $(SERVER) $(patsubst %, $(SSRCD)%.c, $(SSRCS)) \
	-L$(LIBD) -lft -lcurl -I $(INCD) -I $(LIBD)

$(CLIENT) : $(INCD)$(LIB)
	$(CC) $(CFLAGS) -o $(CLIENT) $(patsubst %, $(CSRCD)%.c, $(CSRCS)) \
	-L$(LIBD) -lft -I $(LIBD) -I $(INCD) $(PFLAGS)

debug-multiserver-client : fclean $(INCD)$(LIB) 
	$(CC) $(CFLAGS) $(DFLAGS) -o $(SERVER) $(patsubst %, $(SSRCD)%.c, $(MSRCS)) -L$(LIBD) -lft -I $(INCD)  -I $(LIBD)
	$(CC) $(CFLAGS) $(DFLAGS) -o $(CLIENT) $(patsubst %, $(CSRCD)%.c, $(CSRCS)) -L$(LIBD) -lft -I $(LIBD) -I $(INCD) $(PFLAGS)

debug-multiserver: fclean $(INCD)$(LIB)
	$(CC) $(CFLAGS) $(DFLAGS) -o $(SERVER) $(patsubst %, $(SSRCD)%.c, $(MSRCS)) \
	-L$(LIBD) -lft -I $(INCD)  -I $(LIBD)

debug-server: fclean $(INCD)$(LIB)
	$(CC) $(CFLAGS) $(DFLAGS) -o $(SERVER) $(patsubst %, $(SSRCD)%.c, $(SSRCS)) \
	-L$(LIBD) -lft -lcurl -I $(INCD)  -I $(LIBD)

debug-client: fclean $(INCD)$(LIB)
	$(CC) $(CFLAGS) $(DFLAGS) -o $(CLIENT) $(patsubst %, $(CSRCD)%.c, $(CSRCS)) \
	-L$(LIBD) -lft -I $(LIBD) -I $(INCD) $(PFLAGS)

sanitize-server: fclean $(INCD)$(LIB)
	$(CC) $(CFLAGS) $(SFLAGS) -o $(SERVER) $(patsubst %, $(SSRCD)%.c, $(SSRCS)) \
	-L$(LIBD) -lft -lcurl -I $(LIBD)  -I $(INCD)

sanitize-client: fclean $(INCD)$(LIB)
	$(CC) $(CFLAGS) $(SFLAGS) -o $(CLIENT) $(patsubst %, $(CSRCD)%.c, $(CSRCS)) \
	-L$(LIBD) -lft -I $(LIBD) -I$(INCD) $(PFLAGS)

debug: debug-server debug-client
sanitize: sanitize-server sanitize-client

setup:
	brew tap watsonbox/cmu-sphinx
	brew install --HEAD watsonbox/cmu-sphinx/cmu-sphinxbase
	brew install --HEAD watsonbox/cmu-sphinx/cmu-sphinxtrain
	brew install --HEAD watsonbox/cmu-sphinx/cmu-pocketsphinx

$(INCD)$(LIB):
	make -C $(INCD)libft

clean:
	make -C $(INCD)libft clean
	rm -rf *.o
	#rm -Rrf *.dSYM

fclean: clean
	make -C $(INCD)libft fclean
	rm -rf $(SERVER) $(CLIENT)

re: fclean
	make
