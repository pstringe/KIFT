CC = gcc
INC = ./libft
NAME = hydra
SRCS = hydra.c
OBJS = $(patsubst %.c, %.o, $(SRCS))
LIBD = -L$(INC) -lft
CFLAGS = -Wall -Werror -Wextra -I$(INC) 
OFLAGS =  -o $(NAME) $(OBJS) $(LIBD)
DSRCS = $(SRCS)
DFLAGS = $(CFLAGS) -g $(LIBD) $(DSRCS) -o
DNAME = $(NAME)_debug
DOBJS = $(patsubst %.c, %.o, $(DSRCS))

all: $(NAME)

libft.a : ./libft/Makefile
	make -C ./libft/
$(NAME): libft.a $(OBJS)
	$(CC) $(OFLAGS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
	echo "successful object compilation"

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(DNAME)
	rm -rf $(DNAME).dSYM

re: fclean
	make

debug: $(DNAME)

$(DNAME): fclean
	$(CC) $(DFLAGS) $(DNAME)
	lldb $(DNAME) $(DARGS)
