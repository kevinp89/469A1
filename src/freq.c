#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tsc.h"
#include "freq.h"

double calc_cpu_freq(int num_samples, long ns_timeout)
{
	struct timespec sleep_timer;
	sleep_timer.tv_sec = 0;
	sleep_timer.tv_nsec = ns_timeout;

	double samples[num_samples];
	for(int i = 0; i < num_samples; i++){
		start_counter();
		if(nanosleep(&sleep_timer, NULL) == 0) {
			samples[i] = get_counter();
		} else {
			perror("Error nano-sleeping");
			exit(2);
		}
	}

	double min = samples[0];
	for (int i = 0; i < num_samples; i++) {
		printf("sample[%d]: %f\n", i, samples[i]);
		min = min < samples[i]? min : samples[i];
	}
	printf("min: %f\n", min);

	double cpu_hz = (min / sleep_timer.tv_nsec) * 1e9;
	printf("cpu: %fMHz\n", cpu_hz / 1e6);
	return cpu_hz;
}
