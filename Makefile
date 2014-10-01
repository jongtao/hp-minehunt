CC=gcc
LIBS=-lncurses
CFLAGS=$(LIBS) -Wall -ansi #-g

all:
	gcc $(CFLAGS) main.c -o minehunt

clean:
	rm -rf *.o minehunt
