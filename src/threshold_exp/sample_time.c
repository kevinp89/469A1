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
	u_int64_t t0, t1;
    
    printf("start\tend\ttotal_cycles\n");
	start_counter();
	for (int i = 0; i < num; i++) {
		t0 = get_counter();
		t1 = get_counter();
		printf("%lu\t%lu\t%lu\n", t0, t1, t1-t0);
	}

    return 0;
}
