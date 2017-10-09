#include <stdio.h>
#include <sys/types.h>
#include "tsc.h"

/* Records num inactive periods in the samples array, where an inactive period
 * is determined by whether it is longer than threshold cycles.
 *
 * Note, samples is an array of size 2*num where samples[2*i] = start of period,
 * and samples[2*i+1] = end of period.
 */
u_int64_t inactive_periods(int num, u_int64_t threshold, u_int64_t *samples)
{
	u_int64_t first, prev, curr;

	start_counter();
	first = prev = get_counter();

	for (int idx = 0; idx < num;) {
		curr = get_counter();
		if ((curr - prev) > threshold){ /* Changed: >= to > for e.g. 0 */
			samples[2*idx] = prev;
			samples[2*idx + 1] = curr;
			idx++;
		}
		prev = curr;
	}

	return first;
}

/* Generates listing of active and inactive periods.
 * samples: start and end times of the inactive periods
 * num_periods: number of inactive periods in samples
 * cpu_hz: cpu frequency
 * active_start: start of the first active period
 */
void show_periods(int num_periods, u_int64_t *samples, float cpu_hz, u_int64_t active_start)
{
	u_int64_t inactive_start, inactive_end;

	for (int period = 0; period < num_periods; period++) {
		inactive_start = samples[2*period];
		inactive_end = samples[2*period + 1];

		for (int active = 1; active >= 0; active--) {
			u_int64_t start, duration;
			if (active) {
				start = active_start;
				duration = inactive_start - active_start;
				printf("Active %d: ", period);
			} else {
				start = inactive_start;
				duration = inactive_end - inactive_start;
				printf("Inactive %d: ", period);
			}
			printf("start at %lu, duration %lu cycles (%f ms)\n", start, duration, duration*(1/cpu_hz)*1000);
		}
		active_start = inactive_end;
	}
}
