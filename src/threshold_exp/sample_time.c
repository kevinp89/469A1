#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../tsc.h"
#include "../periods.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num>\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]);
    u_int64_t *samples = malloc(sizeof(*samples) * num * 2);
    inactive_periods(num, 0, samples);
    
    printf("start\tend\ttotal_cycles\n");
    for (int i = 0; i < num; i++) {
        printf("%lu\t%lu\t%lu\n", samples[2*i], samples[2*i+1], samples[2*i+1] - samples[2*i]);
    }

    return 0;
}
