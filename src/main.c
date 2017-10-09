#include <stdio.h>
#include <stdlib.h>
#include "tsc.h"
#include "periods.h"
#include "freq.h"


int main(int argc, char *argv[])
{
	if(argc != 2){
		fprintf(stderr, "Usage: %s <number of inactive periods>\n", argv[0]);
		return 1;
	}

	int num_inactive = atoi(argv[1]);
	u_int64_t *samples = malloc(sizeof(*samples) * num_inactive * 2);
	double hz = calc_cpu_freq(6, 10000000L /* 10 ms */);
	u_int64_t start_active = inactive_periods(num_inactive, 10000, samples);

	u_int64_t start, end, duration;
	for (int period = 0; period < num_inactive; period++) {
		start = samples[2*period];
		end = samples[2*period + 1];
		duration = end - start;

		printf("Inactive %d: start at %lu, duration %lu cycles (xxxxx)\n", period, start, duration);
	}


	return 0;
}
