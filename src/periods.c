#include <sys/types.h>
#include "tsc.h"

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
