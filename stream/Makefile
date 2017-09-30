CC = gcc
CFLAGS = -O2


all: mccalpin-stream

mccalpin-stream: stream.c
	$(CC) $(CFLAGS) -DSTREAM_ARRAY_SIZE=25000000 stream.c -o mccalpin-stream

clean:
	rm -f mccalpin-stream *.o
