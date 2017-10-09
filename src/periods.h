#ifndef PERIODS_H
#define PERIODS_H
u_int64_t inactive_periods(int num, u_int64_t threshold, u_int64_t *samples);
void show_periods(int num_periods, u_int64_t *samples, float cpu_hz, u_int64_t active_start);
#endif
