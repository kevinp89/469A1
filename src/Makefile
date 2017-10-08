CC = gcc
CFLAGS = -Wall
SRC_DIR = ./src

p1: main.c tsc.c tsc.h
	$(CC) $(CFLAGS) -o $@ main.c tsc.c

threshold_tlb: threshold_exp/tlb_miss.c tsc.c
	$(CC) $(CFLAGS) -o $@ $^

threshold_samples: threshold_exp/sample_time.c tsc.c periods.c
	$(CC) $(CFLAGS) -o $@ $^

all: p1

clean:
	rm -f p1
