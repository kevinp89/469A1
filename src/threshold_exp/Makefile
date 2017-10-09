CC = gcc
CFLAGS = -Wall

all: threshold_samples threshold_tlb

threshold_tlb: tlb_miss.c ../tsc.c
	$(CC) $(CFLAGS) -o $@ $^

threshold_samples: sample_time.c ../tsc.c ../periods.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f threshold_tlb threshold_samples

.PHONY: all clean
