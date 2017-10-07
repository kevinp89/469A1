CC = gcc
CFLAGS = -g -Wall
SRC_DIR = ./src

p1: main.c tsc.c tsc.h
	$(CC) $(CFLAGS) -o $@ main.c tsc.c

all: p1

clean:
	rm -f p1
