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
	u_int64_t active_start = inactive_periods(num_inactive, 10000, samples);
	show_periods(num_inactive, samples, hz, active_start);

	return 0;
}
