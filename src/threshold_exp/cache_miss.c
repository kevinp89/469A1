#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../tsc.h"

int main(int argc, char *argv[])
{
	int n = 1024 * 1024; /* 1MB */
    char *block = malloc(n * sizeof(*block));

    u_int64_t t1;
	int ri;
	printf("block\tcycles\taddress\n");
    for (int i = 0; i < 10; i++) {
		ri  = rand() % n;
		start_counter();
        block[ri] = 1;
        t1 = get_counter();
        printf("%d\t%lu\t%p\n", ri, t1, &(block[ri]));
    }

    return 0;
}
