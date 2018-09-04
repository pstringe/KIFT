#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pstringe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/02 14:49:53 by pstringe          #+#    #+#              #
#    Updated: 2018/09/04 13:06:41 by pstringe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = hello
INCD = ./includes/
LIB = libft.a
INCD = ./includes/
SRCD = ./srcs/
LIBD = $(INCD)libft/
SRCS = hello_ps
OBJS = $(patsubst $(SRCD)%, %.o, $(SRCS))
CFLAGS = -Wall -Wextra
DFLAGS = -g
SFLAGS = -fsanitize=address -fno-omit-frame-pointer
PFLAGS = -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" \
		 `pkg-config --cflags --libs pocketsphinx sphinxbase`

all: $(NAME)
$(NAME): $(INCD)$(LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(patsubst %, $(SRCD)%.c, $(SRCS)) -L$(LIBD) -lft -I $(INCD) $(PFLAGS)
debug: fclean $(INCD)$(LIB)
	$(CC) $(CFLAGS) $(DFLAGS) -o $(NAME) $(patsubst %, $(SRCD)%.c, $(SRCS)) -L$(LIBD) -lft -I $(INCD) $(PFLAGS)
sanitize: fclean $(INCD)$(LIB)
	$(CC) $(CFLAGS) $(SFLAGS) -o $(NAME) $(patsubst %, $(SRCD)%.c, $(SRCS)) -L$(LIBD) -lft -I $(INCD) $(PFLAGS)
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
	rm -rf *.dSYM
fclean: clean
	make -C $(INCD)libft fclean
	rm -rf $(NAME)
re: fclean
	make

