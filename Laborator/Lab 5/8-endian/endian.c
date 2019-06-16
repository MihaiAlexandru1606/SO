/**
  * SO, 2016
  * Lab #5
  *
  * Task #8, lin
  *
  * Endianess
  */
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

int main(void) {
    int i;
    unsigned int n = 0xDEADBEEF;
    unsigned char *w;

    /* TODO - use w to show all bytes of n in order */
    i = 1;
    w = &i;
    if (*w < *(w + sizeof(int) - 1)) {
        w = &n;
	    for (int j = 0; j < 4; j++)
	        printf("%X ", *(w + j));
    } else {
        w = &n;
        for (int j = 4; j >= 0; j++)
            printf("%X ", *(w + j));
    }
    return 0;
}

