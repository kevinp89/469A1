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


/**
double get_freq(){

	int count = 1;
	double cmeas=0;
	double cycles;
	
	int CMIN = 50000;
	do{
		start_counter();
		
		cmeas = get_counter();
		cycles = cmeas / count;
		count++;
	
	}while (cmeas < CMIN);

	return cycles * 1e6;
}
**/
int main(int argc, char *argv[])
{

        if(argc != 2){
		fprintf(stderr, "Usage: ./main <number of inactive periods>\n");
	   	exit(1);
	}
		
	int num_inactive = atoi(argv[1]);
	

	struct timespec sleep_timer;	
	sleep_timer.tv_sec = 0;
	sleep_timer.tv_nsec = 1000000L; // 1 milisecond
	
	//int count_miliseconds = 0;
	double samples[6];	
	int i;
	double min = INT_MAX;
	for(i=0; i<6; i++){
		start_counter();
		if(nanosleep(&sleep_timer, NULL) == 0){
			samples[i] = get_counter();
			if(samples[i] < min)
				min = samples[i];
		}	
	}	

	int j;
	for(j=0; j<6; j++){
		printf("sample[%d]: %f\n", j, samples[j]);	
	}
	
	double cpu_hz = (min / 1e6) * 1e9;
	printf("min: %f\n", min);
	printf("cpu: %fMHz\n", cpu_hz/1e6); 
	
	printf("given num inactive: %d\n", num_inactive);
    	/* u_int64_t samples[100]; */
   	// inactive_periods(num_inactive,0, 0);
   	return 0;
}
