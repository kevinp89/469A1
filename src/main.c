#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include "tsc.h"

u_int64_t inactive_periods(int num, u_int64_t threshold, u_int64_t *samples)
{
	int idx;
	//initialize the readings
	u_int64_t initial_reading, prev_reading, current_reading;

	start_counter();
	initial_reading = prev_reading = current_reading = get_counter();

	for(idx=0; idx < num;){
		prev_reading = current_reading;
		current_reading = get_counter();

		if((current_reading - prev_reading) >= threshold){
			samples[2*idx] = prev_reading;
			samples[2*idx + 1] = current_reading;
			idx++;
		}
	}

	return initial_reading;
}

int main(int argc, char *argv[])
{

        if(argc != 2){
		fprintf(stderr, "Usage: ./main <number of inactive periods>");
	   	exit(1);
	}
		
	int num_inactive = atoi(argv[1]);

	struct timespec sleep_timer;	
	sleep_timer.tv_sec = 0;
	sleep_timer.tv_nsec = 1000000L; // 1 milisecond
	
	//int count_miliseconds = 0;
	int samples[4];	
	int i;
	for(i=0; i<3; i++){
		start_counter();
		if(nanosleep(&sleep_timer, NULL) == 0){
			samples[i] = get_counter();
		}
	}
	
	int j;
	for(j=0; j<4; j++){
		printf("sample: %d\n", samples[j]);	
	}
	printf("given num inactive: %d\n", num_inactive);
    	/* u_int64_t samples[100]; */
   	// inactive_periods(num_inactive,0, 0);
   	return 0;
}
