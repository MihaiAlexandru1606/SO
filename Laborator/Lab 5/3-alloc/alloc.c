/**
  * SO, 2016
  * Lab #5
  *
  * Task #3, lin
  *
  * Use of valgrind
  */
#include <stdio.h>
#include <stdlib.h>

#define    MAX        100
#define CHUNK        10
#define SEED        23
#define STOP        17

#define FREE_SAFE(a)            \
        if (a != NULL) {        \
            free(a);            \
            a = NULL;           \
        }

#include "utils.h"

int main(void) {
    int nr, count = 0;
    int *buffer = NULL;

    /* alloc buffer with initial size CHUNK */
    buffer = malloc(CHUNK * sizeof(int));
    DIE(buffer == NULL, "malloc");

    srand(SEED);
    do {
        nr = 1 + rand() % MAX;
        buffer[count] = nr;
        count++;

        if (count % CHUNK == 0) {
            printf("Resize buffer to fit %d elements\n", count);

            /* resize bufferului to fit CHUNK elements */
            FREE_SAFE(buffer);

            buffer = malloc((count + CHUNK) * sizeof(int));
            DIE(buffer == NULL, "malloc");
        }

        printf("buffer[%d]=%d\n", count - 1, buffer[count - 1]);

    } while (buffer[count - 1] != STOP);

    FREE_SAFE(buffer);
    return 0;
}
