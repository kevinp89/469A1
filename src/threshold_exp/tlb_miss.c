#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../tsc.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_pages>\n", argv[0]);
        return 1;
    }

    printf("# TLB MISS\n");

    int page_size = getpagesize();
    int pages = atoi(argv[1]);
    char *block = malloc(sizeof(*block) * page_size * pages);
    printf("# pagesize=%d\tallocated=%zu\n", page_size, sizeof(*block) * page_size * pages);

    printf("byte\ttime\taddr\n");
    u_int64_t t0, t1;
    int target_byte;
    start_counter();
    for (int i = 0; i < pages; i++) {
        target_byte = i*page_size;
        t0 = get_counter();
        block[target_byte] = 0;
        t1 = get_counter();
        printf("%d\t%lu\t%p\n", target_byte, t1-t0, &(block[target_byte]));
    }
    return 0;
}
