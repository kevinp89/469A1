#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tsc.h"
#include "periods.h"
#include "freq.h"


struct options {
	int inactive_periods;
};

void usage(char *name)
{
	printf("Usage: %s -n <num inactive periods>\n" , name);
}

int parse_args(int argc, char **argv, struct options *args)
{
	// defaults
	args->inactive_periods = -1;

	// parse the new stuff
	int opt;
	while ((opt = getopt(argc, argv, "hn:")) != -1) {
		switch (opt) {
			case 'n': 
				args->inactive_periods = atoi(optarg);
				break;
			case 'h':
				usage(argv[0]);
				return 1;
				break;
			default:
				fprintf(stderr, "Unknown option '%c'.\n", optopt);
				return 1;
				break;
		}
	}

	// validation
	if (args->inactive_periods < 0) {
		fprintf(stderr, "Error: '-n' must be specified.\n");
		usage(argv[0]);
		return 1;
	}

	return 0;
}


int main(int argc, char *argv[])
{
	struct options args;
	if (parse_args(argc, argv, &args) != 0) {
		return 1;
	}

	int num_inactive = args.inactive_periods;
	u_int64_t *samples = malloc(sizeof(*samples) * num_inactive * 2);
	double hz = calc_cpu_freq(6, 10000000L /* 10 ms */);
	u_int64_t active_start = inactive_periods(num_inactive, 10000, samples);
	show_periods(num_inactive, samples, hz, active_start);

	return 0;
}
