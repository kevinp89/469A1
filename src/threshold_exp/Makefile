CC = gcc
CFLAGS = -Wall

all: cache_miss successive_samples 

cache_miss: cache_miss.c ../tsc.c
	$(CC) $(CFLAGS) -o $@ $^

successive_samples: sample_time.c ../tsc.c ../periods.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f cache_miss successive_samples 

.PHONY: all clean
