#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
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
			samples[idx] = current_reading;
			idx++;
		}
	}


	return initial_reading;
}

int main(int argc, char *argv[])
{
    /* u_int64_t samples[100]; */
    inactive_periods(0,0, 0);
    return 0;
}
