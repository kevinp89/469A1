CC = gcc
CFLAGS = -Wall

all: p1

p1: main.c tsc.c periods.c freq.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f p1
