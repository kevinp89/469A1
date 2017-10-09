#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <limits.h>
#include "tsc.h"
#include "periods.h"

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

int main(int argc, char *argv[])
{
    if(argc != 2){
		fprintf(stderr, "Usage: %s <number of inactive periods>\n", argv[0]);
	   	return 1;
	}

	/* int num_inactive = atoi(argv[1]); */

    double hz = calc_cpu_freq(6, 10000000L /* 10 ms */);

	
   	return 0;
}
